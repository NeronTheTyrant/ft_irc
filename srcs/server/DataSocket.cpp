#include "DataSocket.hpp"
#include <cerrno>

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

