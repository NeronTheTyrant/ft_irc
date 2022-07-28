#include "Network.hpp"

Network::Network() {};

Network::~Network() {};

void	add(User * user) {
	_userSockets[user->sd()] = user;
	if (user->nickname().size())
		_users[user->nickname()] = user;
}

void	add(Channel * channel) {
	_channels[channel->name()] = channel;
}

void	remove(User * user) {
	_users.erase(user->nickname());
}

void	remove(Channel * channel) {
	_channels.erase(channel->name());
}

User *	getUserByName(std::string const nickname) {
	Users::iterator it = _users.find(nickname);
	if (it == _users.end())
		return nullptr;
	else
		return it->second;
}

User *	getUserBySocket(int sd) {
	UserSockets::iterator it = _userSockets.find(sd);
	if (it == _userSockets.end())
		return nullptr;
	else
		return it->second;
}

Channel *	getChannelByName(std::string const channelName) {
	Channels::iterator it = _channels.find(channelName);
	if (it == _channels.end())
		return nullptr;
	else
		return it->second;
}
