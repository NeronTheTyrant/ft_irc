#ifndef IRCSERVER_HPP
#define IRCSERVER_HPP

#include "Network.hpp"
#include "../sockets/EpollHandler.hpp"
#include "../sockets/IRCEventListener.hpp"

class IRCServer {
public:
	IRCServer(int16_t port);
	~IRCServer();

	void		start();
	Network &	network();
	EpollHandler &	epollHandler();

private:
	Network				_network;
	EpollHandler		_epollHandler;
	IRCEventListener *	_eventListener;
}

#endif
