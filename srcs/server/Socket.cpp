
#include "Socket.hpp"
/* Socket */

Socket::Socket()
	: sd(Socket::invalid_socket) {}

Socket::~Socket() {
	if (sd != Socket::invalid_socket) {
		close(sd);
	}
}

Socket::Socket(Socket & o)
	:sd (Socket::invalid_socket) {
	std::swap(sd, o.sd);
}

Socket::Socket(int sd)
	: sd(sd) {
	if (sd == Socket::invalid_socket){
		throw std::logic_error("Socket initialised with invalid socket descriptor");
	}
}

Socket &	Socket::operator=(Socket & o) {
	std::swap(sd, o.sd);
	return *this;
}

bool		Socket::operator==(Socket & o) {
	if (getsd() == o.getsd())
		return true;
	else
		return false;
}

const int Socket::invalid_socket = -1;

