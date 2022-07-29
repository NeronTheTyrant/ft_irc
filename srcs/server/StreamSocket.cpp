
#include"StreamSocket.hpp"

/* StreamSocket */

StreamSocket::StreamSocket()
	: Socket(socket(AF_INET, SOCK_STREAM, 0)) {}

StreamSocket::StreamSocket(int sd)
	: Socket(sd) {}
