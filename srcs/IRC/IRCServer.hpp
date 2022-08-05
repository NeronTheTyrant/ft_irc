#ifndef IRCSERVER_HPP
#define IRCSERVER_HPP

#include "Network.hpp"
#include "EpollHandler.hpp"
#include "IRCEventListener.hpp"
#include <map>
#include <vector>

class IRCEventListener;

class IRCServer {

	typedef	std::map<std::string, void	(IRCServer::*) (User &, std::vector<std::string>)>	mapCommand;

public:
	IRCServer(uint16_t port);
	~IRCServer();

	void		start();
	std::string	name();
	Network &	network();
	EpollHandler &	epollHandler();

	/**
	 * COMMAND FUNCTION
	*/
	void	pass(User & user, std::vector<std::string> params);
	void	nick(User & user, std::vector<std::string> params);
	void	user(User & user, std::vector<std::string> params);
	void	quit(User & user, std::vector<std::string> params);
	void	privmsg(User & user, std::vector<std::string> params);
	void	notice(User & user, std::vector<std::string> params);
	void	join(User & user, std::vector<std::string> params);
	void	list(User & user, std::vector<std::string> params);
	void	names(User & user, std::vector<std::string> params);
	void	mode(User & user, std::vector<std::string> params);
	void	oper(User & user, std::vector<std::string> params);
	void	topic(User & user, std::vector<std::string> params);
	void	motd(User & user, std::vector<std::string> params);
	void	ping(User & user, std::vector<std::string> params);
	void	pong(User & user, std::vector<std::string> params);
	void	away(User & user, std::vector<std::string> params);
	void	die(User & user, std::vector<std::string> params);
	void	kill(User & user, std::vector<std::string> params);
	void	kick(User & user, std::vector<std::string> params);

private:
	std::string			_name;
	Network				_network;
	EpollHandler		_epollHandler;
	IRCEventListener *	_eventListener;
	mapCommand			_commands;

};

#endif
