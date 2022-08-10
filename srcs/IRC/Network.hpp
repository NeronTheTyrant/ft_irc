#ifndef NETWORK_HPP
#define NETWORK_HPP

# include <map>
# include <iostream>
# include <list>
# include "User.hpp"
# include "Channel.hpp"
# include "utils.hpp"

class Network { // Stores User and Channel maps, has methods to add and remove user and channels
public:
	typedef std::map<int, User *>				UserSockets;
	typedef std::map<std::string, User *>		Users;
	typedef std::map<std::string, Channel *>	Channels;

	Network();
	~Network();

	Users &			users();
	Channels &		channels();
	UserSockets &	userSockets();

	void	add(User * user);
	void	add(Channel * channel);
	void	remove(User * user);
	void	remove(Channel * channel);

	User *					getUserByName(std::string const nickname);
	User *					getUserBySocket(int sd);
	Channel *				getChannelByName(std::string const channelName);
	std::list<Channel *>	getUserChannelList(User * u);

private:
	Users		_users;
	Channels	_channels;
	UserSockets	_userSockets;
};

#endif
