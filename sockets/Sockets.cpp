#include <cstdint>
#include <string>
#include "Sockets.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <stdexcept>
/* Socket */

Socket::Socket()
	: sd(Socket::invalid_socket), has_error(false) {}

Socket::~Socket() {
	if (sd != Socket::invalid_socket) {
		close(sd);
	}
}

Socket::Socket(Socket & o)
	:sd (Socket::invalid_socket), has_error(false) {
	std::swap(sd, o.sd);
	std::swap(has_error, o.has_error);
}

Socket::Socket(int sd)
	: sd(sd) {
	if (sd == Socket::invalid_socket){
		throw std::logic_error("Socket initialised with invalid socket descriptor");
	}
}

Socket &	Socket::operator=(Socket & o) {
	std::swap(sd, o.sd);
	std::swap(has_error, o.has_error);
	return *this;
}

bool		Socket::operator==(Socket & o) {
	if (getsd() == o.getsd())
		return true;
	else
		return false;
}

const int Socket::invalid_socket = -1;

/* StreamSocket */

StreamSocket::StreamSocket()
	: Socket(socket(AF_INET, SOCK_STREAM, 0)) {}

StreamSocket::StreamSocket(int sd)
	: Socket(sd) {}

/* DataSocket */

DataSocket::DataSocket()
	: StreamSocket(socket(AF_INET, SOCK_STREAM, 0)) {}

DataSocket::DataSocket(int sd)
	: StreamSocket(sd) {}

/* send() wrapper */

void	DataSocket::send (const char * data, std::size_t len) {
	std::size_t	sent = 0;
	while (sent < len) {
		long int	ret = ::send(sd, data + sent, len - sent, MSG_NOSIGNAL);
		if (ret == -1) {
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				continue;
			else
				throw std::runtime_error(std::string("send error: ") + strerror(errno));
		}
		sent += ret;
	}
}

/* recv() wrapper */

void	DataSocket::recv (char * data, std::size_t len) {
	std::size_t received = 0;
	while (received < len) {
		long int	ret = ::recv(sd, data + received, len - received, 0);
		if (ret == -1)
			throw std::runtime_error(std::string("recv error: ") + strerror(errno));
		if (ret == 0)
			throw std::runtime_error("remote closed");
		received += ret;
	}
}

/* ServerSocket */

ServerSocket::ServerSocket(std::uint16_t port) 
	: StreamSocket(socket(AF_INET, SOCK_STREAM, 0)), port(port) {
}


/* setsockopt, fcntl (nonblockable) and bind */

void	ServerSocket::init() {
	try {
		const int opt = 1;
		const int backlog = 128;
		int ret = setsockopt(sd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
		if (ret < 0)
			throw std::runtime_error(std::string("setsockopt failed: ") + strerror(errno));
		ret = fcntl(sd, F_SETFL, opt | O_NONBLOCK);
		if (ret != 0)
			throw std::runtime_error(std::string("fcntl failed: ") + strerror(errno));
		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		ret = bind(sd, reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr));
		if (ret != 0)
			throw std::runtime_error(std::string("bind failed: ") + strerror(errno));
	}
	catch (const std::exception &) {
		close(sd);
		throw;
	}
}

/* Start listening */

void	ServerSocket::start() {
	try {
		const int backlog = 128;
		int ret = listen(sd, backlog);
		if (ret != 0)
			throw std::runtime_error(std::string("listen failed: ") + strerror(errno));
	}
	catch (const std::exception &) {
		close(sd);
		throw;
	}
}

/* Accept entering connection and return DataSocket */

int ServerSocket::accept() {
	struct sockaddr	addr;
	socklen_t	addrlen = sizeof(addr);
	int ret = ::accept(sd, &addr, &addrlen);
	if (ret < 0)
		throw std::runtime_error(std::string("accept failed: ") + strerror(errno));
	return ret;
}
