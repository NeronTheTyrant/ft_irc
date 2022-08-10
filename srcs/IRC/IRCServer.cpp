#include "IRCServer.hpp"

IRCServer::IRCServer(uint16_t port, std::string const & name, std::string const & password) :
	_name(name), _password(password), _epollHandler(port) {;
	_commands["PASS"]		= &IRCServer::pass;
	_commands["NICK"]		= &IRCServer::nick;
	_commands["USER"]		= &IRCServer::user;
//	_commands["QUIT"]		= &IRCServer::quit;
//	_commands["PRIVMSG"]	= &IRCServer::privmsg;
//	_commands["NOTICE"]		= &IRCServer::notice;
//	_commands["JOIN"]		= &IRCServer::join;
//	_commands["LIST"]		= &IRCServer::list;
//	_commands["NAMES"]		= &IRCServer::names;
//	_commands["MODE"]		= &IRCServer::mode;
//	_commands["OPER"]		= &IRCServer::oper;
//	_commands["TOPIC"]		= &IRCServer::topic;
//	_commands["MOTD"]		= &IRCServer::motd;
//	_commands["PING"]		= &IRCServer::ping;
//	_commands["PONG"]		= &IRCServer::pong;
//	_commands["AWAY"]		= &IRCServer::away;
//	_commands["DIE"]		= &IRCServer::die;
//	_commands["KILL"]		= &IRCServer::kill;
//	_commands["KICK"]		= &IRCServer::kick;
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

std::string IRCServer::password() {
	return _password;
}

Network &	IRCServer::network() {
	return _network;
}

EpollHandler &	IRCServer::epollHandler() {
	return _epollHandler;
}

void	IRCServer::disconnect(User * u, std::string quitReason) {
	epollHandler().disconnectClient(u->sd(), quitReason);
}

void	IRCServer::clearUser(User * u, std::string quitReason) {
	std::string	quitMessage = serverMessageBuilder(*u, "QUIT :") + quitReason;

	// iterate through channels, kick user from each channel
	std::list<Channel *> chanList = network().getUserChannelList(u);
	for (std::list<Channel *>::iterator it = chanList.begin(); u->channelCount() && it != chanList.end(); it++) {
		(*it)->send(quitMessage, u);
		(*it)->removeUser(u);
		// if channel is empty after this, delete channel
		if (!(*it)->userCount()) {
			network().remove(*it);
		}
	}
	u->send(std::string("ERROR :") + "(" + quitReason + ")");
	network().remove(u);
}
