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
		_users[strToUpper(user->nickname())] = user;
}

void	Network::add(Channel * channel) {
	_channels[strToUpper(channel->name())] = channel;
}

void	Network::remove(User * user) {
	_users.erase(strToUpper(user->nickname()));
	_userSockets.erase(user->sd());
}

void	Network::remove(Channel * channel) {
	channel->clearUsers();
	_channels.erase(strToUpper(channel->name()));
	delete channel;
}

User *	Network::getUserByName(std::string const nickname) {
	Users::iterator it = _users.find(strToUpper(nickname));
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
	Channels::iterator it = _channels.find(strToUpper(channelName));
	if (it == _channels.end())
		return u_nullptr;
	else
		return it->second;
}

std::set<Channel *>	Network::getUserChannelList(User * u) {
	return u->channelList();
}

std::string Network::getVisibleUsersNotInChan(User * u) {
	std::string ret("");
	for (Users::iterator it = users().begin(); it != users().end(); it++) {
		if (u->channelCount() == 0
				&& (it->second->isModeSet(UserMode::INVISIBLE) == false || u->isRelated(it->second))) {
			if (it != users().begin()) {
				ret += ' ';
			}
			ret += it->second->nickname();
		}
	}
	return ret;
}
