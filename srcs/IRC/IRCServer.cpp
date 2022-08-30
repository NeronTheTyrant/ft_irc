#include "IRCServer.hpp"
#include <ctime>

IRCServer::IRCServer(uint16_t port, std::string const & password) :
	_name("chaussette.irc.net"), _password(password), _epollHandler(port), _eventListener (NULL), _restartFlag(false) {

	_operatorList["Agathe"] = std::make_pair("Thepower", std::vector<std::string> (1, "127.0.0.1") );

	_commands["CAP"]		= &IRCServer::cap;	
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
	_commands["MOTD"]		= &IRCServer::motd;
	_commands["PING"]		= &IRCServer::ping;
//	_commands["PONG"]		= &IRCServer::pong;
	_commands["PART"]		= &IRCServer::part;
	_commands["AWAY"]		= &IRCServer::away;
	_commands["DIE"]		= &IRCServer::die;
	_commands["KILL"]		= &IRCServer::kill;
	_commands["KICK"]		= &IRCServer::kick;
	_commands["RESTART"]	= &IRCServer::restart;
	_commands["WALLOPS"]	= &IRCServer::wallops;
};

IRCServer::~IRCServer() {
	clear("Shutting Down");
	if (_eventListener)
		delete _eventListener;
};

void	IRCServer::initCreationTime(){

	time_t	tmpTime = time(NULL);
	struct tm * timeinfo = localtime(&tmpTime);
	_creationTime = asctime(timeinfo);
	if (_creationTime.size() > 0) {
		_creationTime.erase(_creationTime.size() - 1, 1);
	}
}

void	IRCServer::setInterruptFlag() {
	_epollHandler.setInterruptFlag();
}

void	IRCServer::run() {
	free_from_signal(this);

	struct sigaction	sa = {};
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &IRCsigHandler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGHUP, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);

	initCreationTime();
	_epollHandler.initMasterSocket();
	_eventListener = new IRCEventListener(*this);
	_epollHandler.addEventListener(_eventListener);
	_epollHandler.run();
	while (_restartFlag) {
		initCreationTime();
		_restartFlag = false;
		_epollHandler.restart();
	}
}

void	IRCServer::stop() {
	_epollHandler.stop();
}

std::string	IRCServer::creationTime() const {
	return _creationTime;
}

std::string	IRCServer::name() const {
	return _name;
}

std::string IRCServer::password() const {
	return _password;
}

Network &	IRCServer::network() {
	return _network;
}

EpollHandler &	IRCServer::epollHandler() {
	return _epollHandler;
}

void	IRCServer::disconnect(User * u, std::string quitReason, bool notify) {
	epollHandler().disconnectClient(u->sd(), quitReason, notify);
}

void	IRCServer::clearUser(User * u, std::string quitReason, bool notify) {
	std::string	quitMessage = serverMessageBuilder(*u, std::string("QUIT :") + quitReason);

	// iterate through channels, kick user from each channel
	std::set<Channel *> chanList = u->channelList();
	for (std::set<Channel *>::iterator it = chanList.begin(); u->channelCount() && it != chanList.end(); it++) {
		if (notify) {
			u->send(serverMessageBuilder(*u, std::string("PART ") + (*it)->name() + " :" + quitReason));
		}
		(*it)->removeUser(u);
		if (!(*it)->userCount()) {
			network().remove(*it);
		}
		else {
			(*it)->send(quitMessage, u);
		}
		// if channel is empty after this, delete channel
	}
	if (notify) {
		u->send(serverMessageBuilder(*this, std::string("ERROR :") + "(" + quitReason + ")"));
	}
	network().remove(u);
}

void	IRCServer::clear(std::string reason) {
	Network::Users users = network().users();
	for (Network::Users::iterator it = users.begin(); it != users.end(); ++it) {
		disconnect(it->second, reason);
	}
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

std::string	IRCServer::botmsg(std::string botName, std::string str) {
	std::string prefix;

	prefix = ":" + botName + "!botman@chaussette.irc.net ";
	return prefix + str + "\r\n";
}

void	free_from_signal(IRCServer * ptr) {
	static IRCServer * mem = u_nullptr;

	if (ptr != u_nullptr) {
		mem = ptr;
	}
	else {
		mem->clear("Server closed by signal");
		mem->stop();
		mem->setInterruptFlag();
	}
}
