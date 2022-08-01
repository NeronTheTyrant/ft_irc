#include "IRCServer.hpp"

IRCServer::IRCServer(int16_t port) :
	_epollHandler(port) {};

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

Network &	IRCServer::network() {
	return _network;
}

EpollHandler &	IRCServer::epollHandler() {
	return _epollHandler;
}
