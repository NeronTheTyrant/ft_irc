#ifndef IRCSERVER_HPP
# define IRCSERVER_HPP

# include <map>
# include <vector>
# include <ctime>
# include <signal.h>

# include "Network.hpp"
# include "EpollHandler.hpp"
# include "IRCEventListener.hpp"
# include "messageBuilder.hpp"
# include "Command.hpp"

#define RPLMESSAGE(code) serverMessageBuilder(*this, commandMessageBuilder(code))

class IRCEventListener;

class IRCServer {

	typedef	std::map<std::string, void	(IRCServer::*) (User *, std::vector<std::string>)>	Commands;
	typedef std::map<std::string, std::pair<std::string, std::vector<std::string> > >		Operators;

public:
	IRCServer(uint16_t port, std::string const & password);
	~IRCServer();

	std::string	creationTime() const;
	std::string	name() const;
	std::string password() const;
	Network &	network();
	EpollHandler &	epollHandler();

	void		setInterruptFlag();

	void		initCreationTime();
	void		run();
	void		stop();

	void	disconnect(User * u, std::string quitReason, bool notify = true);
	void	clearUser(User * u, std::string quitReason, bool notify = true);

	void	clear(std::string reason);

	void	addToRemoveList(User * user);
	void	clearRemoveList();

	void	execCommand(User * u, Command command);

	std::string botmsg(std::string botName, std::string str);

	/**
	 * COMMAND FUNCTION
	*/
	void	cap(User * user, std::vector<std::string> params);
	void	pass(User * user, std::vector<std::string> params);
	void	nick(User * user, std::vector<std::string> params);
	void	user(User * user, std::vector<std::string> params);
	void	quit(User * user, std::vector<std::string> params);
	void	privmsg(User * user, std::vector<std::string> params);
	void	notice(User * user, std::vector<std::string> params);
	void	join(User * user, std::vector<std::string> params);
	void	invite(User * user, std::vector<std::string> params);
	void	list(User * user, std::vector<std::string> params);
	void	names(User * user, std::vector<std::string> params);
	void	mode(User * user, std::vector<std::string> params);
	void	oper(User * user, std::vector<std::string> params);
	void	topic(User * user, std::vector<std::string> params);
	void	motd(User * user, std::vector<std::string> params);
	void	ping(User * user, std::vector<std::string> params);
	void	pong(User * user, std::vector<std::string> params);
	void	part(User * user, std::vector<std::string> params);
	void	away(User * user, std::vector<std::string> params);
	void	die(User * user, std::vector<std::string> params);
	void	kill(User * user, std::vector<std::string> params);
	void	kick(User * user, std::vector<std::string> params);
	void	restart(User * user, std::vector<std::string> params);
	void	wallops(User * user, std::vector<std::string> params);

	/**
	 * UTILS
	 */
	bool	checkTopicError(User * sender, std::vector<std::string> params);
private:
	std::string							_name;
	std::string							_password;
	Operators							_operatorList;
	Network								_network;
	EpollHandler						_epollHandler;
	IRCEventListener *					_eventListener;
	Commands							_commands;
  	std::list<User *>					_removeList;
	bool								_restartFlag;
	std::string							_creationTime;


};

bool	validChan(std::string chanName);
void	free_from_signal(IRCServer * ptr);

#endif
