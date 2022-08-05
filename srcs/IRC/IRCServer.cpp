#include "IRCServer.hpp"

IRCServer::IRCServer(uint16_t port, std::string const & name, std::string const & password) :
	_name(name), _password(password), _epollHandler(port) {};

IRCServer::~IRCServer() {
	if (_eventListener)
		delete _eventListener;
};

void	IRCServer::start() {
	_epollHandler.initMasterSocket();
	IRCEventListener *	irc_event_listener = new IRCEventListener(*this);
	_epollHandler.addEventListener(irc_event_listener);
	_epollHandler.run();
}

std::string	IRCServer::name() {
	return _name;
}

std::string IRCServer::password() {
	return _password;
}

Network &	IRCServer::network() {
	return _network;
}

EpollHandler &	IRCServer::epollHandler() {
	return _epollHandler;
}
