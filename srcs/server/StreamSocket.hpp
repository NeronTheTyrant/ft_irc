#ifndef STREAMSOCKET_HPP
#define STREAMSOCKET_HPP

#include <cstdint>
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

#include "Socket.hpp"

/* Stream Socket class, initialises socket as STEAM_SOCKET using socket() */

class StreamSocket : public Socket {
public:
	StreamSocket();
	explicit StreamSocket(int sd);
};

#endif
