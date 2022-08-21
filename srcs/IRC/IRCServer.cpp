#include "IRCServer.hpp"

IRCServer::IRCServer(uint16_t port, std::string const & name, std::string const & password, std::map<std::string, std::pair<std::string, std::vector<std::string> > > const & operatorList) :
	_name(name), _password(password), _operatorList(operatorList), _epollHandler(port), _eventListener (NULL) {;
	_commands["PASS"]		= &IRCServer::pass;
	_commands["NICK"]		= &IRCServer::nick;
	_commands["USER"]		= &IRCServer::user;
	_commands["QUIT"]		= &IRCServer::quit;
	_commands["PRIVMSG"]	= &IRCServer::privmsg;
	_commands["NOTICE"]		= &IRCServer::notice;
	_commands["JOIN"]		= &IRCServer::join;
	_commands["INVITE"]		= &IRCServer::invite;
	_commands["LIST"]		= &IRCServer::list;
	_commands["NAMES"]		= &IRCServer::names;
	_commands["MODE"]		= &IRCServer::mode;
	_commands["OPER"]		= &IRCServer::oper;
	_commands["TOPIC"]		= &IRCServer::topic;
//	_commands["MOTD"]		= &IRCServer::motd;
//	_commands["PING"]		= &IRCServer::ping;
//	_commands["PONG"]		= &IRCServer::pong;
	_commands["PART"]		= &IRCServer::part;
	_commands["AWAY"]		= &IRCServer::away;
//	_commands["DIE"]		= &IRCServer::die;
	_commands["KILL"]		= &IRCServer::kill;
	_commands["KICK"]		= &IRCServer::kick;
};

IRCServer::~IRCServer() {
	if (_eventListener)
		delete _eventListener;
};

void	IRCServer::start() {
	_epollHandler.initMasterSocket();
	_eventListener = new IRCEventListener(*this);
	_epollHandler.addEventListener(_eventListener);
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
	std::string	quitMessage = serverMessageBuilder(*u, std::string("QUIT :") + quitReason);

	// iterate through channels, kick user from each channel
	std::set<Channel *> chanList = u->channelList();
	for (std::set<Channel *>::iterator it = chanList.begin(); u->channelCount() && it != chanList.end(); it++) {
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

void	IRCServer::execCommand(User * user, Command command) {
	if (command.command().empty())
		return ;
	Commands::iterator it = _commands.find(command.command());
	if (it == _commands.end()) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_UNKNOWNCOMMAND, user, command.command())));
		return;
	}
	(this->*(it->second))(user, command.arguments());
}

void	IRCServer::addToRemoveList(User * user) {
	_removeList.push_back(user);
}

void	IRCServer::clearRemoveList() {
	if (_removeList.empty())
		return ;
	for (std::list<User *>::iterator it = _removeList.begin(); it != _removeList.end(); it++) {
		delete *it;
	}
	_removeList.clear();
}
