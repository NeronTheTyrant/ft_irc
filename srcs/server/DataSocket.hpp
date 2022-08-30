#ifndef DATASOCKET_HPP
#define DATASOCKET_HPP

/* DataSocket, can send and receive data on socket descriptor, assuming there is an active connection */

#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <stdexcept>
# include <iostream>

#include "StreamSocket.hpp"

class DataSocket : public StreamSocket {
public:
	DataSocket();
	explicit DataSocket(int sd);

	void	send (const char * data, std::size_t len);
	void	recv (char * data, std::size_t len);
};

#endif
