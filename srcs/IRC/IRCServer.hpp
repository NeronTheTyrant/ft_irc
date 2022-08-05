#ifndef IRCSERVER_HPP
#define IRCSERVER_HPP

#include "Network.hpp"
#include "EpollHandler.hpp"
#include "IRCEventListener.hpp"

class IRCEventListener;

class IRCServer {
public:
	IRCServer(uint16_t port, std::string const & name, std::string const & password);
	~IRCServer();

	void		start();
	std::string	name();
	std::string password();
	Network &	network();
	EpollHandler &	epollHandler();

private:
	std::string			_name;
	std::string			_password;
	Network				_network;
	EpollHandler		_epollHandler;
	IRCEventListener *	_eventListener;
};

#endif
