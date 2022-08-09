#include "Network.hpp"

Network::Network() {};

Network::~Network() {};

Network::Users &	Network::users() {
	return _users;
}

Network::Channels &	Network::channels() {
	return _channels;
}

Network::UserSockets & Network::userSockets() {
	return _userSockets;
}

void	Network::add(User * user) {
	_userSockets[user->sd()] = user;
	if (user->nickname().size())
		_users[user->nickname()] = user;
}

void	Network::add(Channel * channel) {
	_channels[channel->name()] = channel;
}

void	Network::remove(User * user) {
	_users.erase(user->nickname());
	_userSockets.erase(user->sd());
}

void	Network::remove(Channel * channel) {
	_channels.erase(channel->name());
}

User *	Network::getUserByName(std::string const nickname) {
	Users::iterator it = _users.find(nickname);
	if (it == _users.end())
		return u_nullptr;
	else
		return it->second;
}

User *	Network::getUserBySocket(int sd) {
	UserSockets::iterator it = _userSockets.find(sd);
	if (it == _userSockets.end())
		return u_nullptr;
	else
		return it->second;
}

Channel *	Network::getChannelByName(std::string const channelName) {
	Channels::iterator it = _channels.find(channelName);
	if (it == _channels.end())
		return u_nullptr;
	else
		return it->second;
}

std::list<Channel *>	Network::getUserChannelList(User * u) {
	std::list<Channel *>	channelList;
	for (Channels::iterator it = channels().begin(); it != channels().end(); it++) {
		if (it->second->isUser(u)) {
			channelList.push_back(it->second);
		}
	}
	return channelList;
}

