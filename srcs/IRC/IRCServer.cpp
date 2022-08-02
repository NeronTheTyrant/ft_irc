#include "IRCServer.hpp"

IRCServer::IRCServer(int16_t port) :
	_epollHandler(port) {
	_commands["PASS"]		= &IRCServer::pass;
	_commands["NICK"]		= &IRCServer::nick;
	_commands["USER"]		= &IRCServer::user;
	_commands["QUIT"]		= &IRCServer::quit;
	_commands["PRIVMSG"]	= &IRCServer::privmsg;
	_commands["NOTICE"]		= &IRCServer::notice;
	_commands["JOIN"]		= &IRCServer::join;
	_commands["LIST"]		= &IRCServer::list;
	_commands["NAMES"]		= &IRCServer::names;
	_commands["MODE"]		= &IRCServer::mode;
	_commands["OPER"]		= &IRCServer::oper;
	_commands["TOPIC"]		= &IRCServer::topic;
	_commands["MOTD"]		= &IRCServer::motd;
	_commands["PING"]		= &IRCServer::ping;
	_commands["PONG"]		= &IRCServer::pong;
	_commands["AWAY"]		= &IRCServer::away;
	_commands["DIE"]		= &IRCServer::die;
	_commands["KILL"]		= &IRCServer::kill;
	_commands["KICK"]		= &IRCServer::kick;
};

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
