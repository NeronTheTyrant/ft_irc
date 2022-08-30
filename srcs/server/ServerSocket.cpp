#include "ServerSocket.hpp"
#include <cerrno>

/* ServerSocket */

ServerSocket::ServerSocket(uint16_t port) 
	: StreamSocket(socket(AF_INET, SOCK_STREAM, 0)), port(port) {
}

void	ServerSocket::reinit() {
	close(sd);
	sd = socket(AF_INET, SOCK_STREAM, 0);
	init();
}

/* setsockopt, fcntl (nonblockable) and bind */

void	ServerSocket::init() {
	try {

		const int opt = 1;
		int ret = setsockopt(sd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
		if (ret < 0)
			throw std::runtime_error(std::string("setsockopt failed: ") + strerror(errno));
		ret = fcntl(sd, F_SETFL, opt | O_NONBLOCK);
		if (ret != 0)
			throw std::runtime_error(std::string("fcntl failed: ") + strerror(errno));
		struct sockaddr_in addr = {};
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		ret = bind(sd, reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr));
		if (ret != 0)
			throw std::runtime_error(std::string("bind failed: ") + strerror(errno));
	}
	catch (const std::exception &e) {
		close(sd);
		throw e;
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
