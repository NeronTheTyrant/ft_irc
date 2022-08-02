#ifndef IRCSERVER_HPP
#define IRCSERVER_HPP

#include "Network.hpp"
#include "EpollHandler.hpp"
#include "IRCEventListener.hpp"

class IRCEventListener;

class IRCServer {
public:
	IRCServer(uint16_t port);
	~IRCServer();

	void		start();
	std::string	name();
	Network &	network();
	EpollHandler &	epollHandler();

private:
	std::string			_name;
	Network				_network;
	EpollHandler		_epollHandler;
	IRCEventListener *	_eventListener;
};

#endif
