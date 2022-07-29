#ifndef SERVERSOCKET_HPP
#define SERVERSOCKET_HPP

#include <cstdint>
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
/* Server socket that can accept connections */

//class StreamSocket;

class ServerSocket : public StreamSocket {
public:
	ServerSocket(std::uint16_t port);
	
	void	init();
	void	start();
	int		accept();

	uint16_t	port;
};

#endif
