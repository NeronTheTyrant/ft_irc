#include "Channel.hpp"

ChannelMode::ChannelMode(uint32_t flag /*= 0*/)
	: Flag(flag) {}

ChannelMode::~ChannelMode() {}

ChannelMode::Mode	ChannelMode::translate(char c) {
	switch (c) {
		case 'm' :
			return MODERATED;
		case 't' :
			return TOPIC;
		default:
			return ERROR;
	}
}

char	ChannelMode::translate(ChannelMode::Mode m) {
	switch (m) {
		case MODERATED :
			return 'm';
		case TOPIC :
			return 't';
		case ERROR :
			return '\0';
	}
	return '\0';
}

MemberStatus::MemberStatus(uint32_t flag /*= 0*/)
	: Flag(flag) {}

MemberStatus::~MemberStatus() {}

MemberStatus::Status	MemberStatus::translate(char c) {
	switch (c) {
		case 'O' :
			return CREATOR;
		case 'o' :
			return OPERATOR;
		case 'v' :
			return VOICE;
		default:
			return ERROR;
	}
}

char	MemberStatus::translate(MemberStatus::Status s) {
	switch (s) {
		case CREATOR :
			return 'O';
		case OPERATOR :
			return 'o';
		case VOICE :
			return 'v';
		case ERROR :
			return '\0';
	}
	return '\0';
}

/**
 * Constructors & Destructors
 */

Channel::Channel(std::string name, User * creator)
	: _name(name), _userCount(0) {
	addUser(creator, MemberStatus(MemberStatus::CREATOR));
}

/**
 * Getters
 */

std::string	Channel::name() const {
	return _name;
}

std::string	Channel::password() const {
	return _password;
}

Channel::Users &	Channel::users() {
	return _users;
}

MemberStatus	Channel::userStatus(User * u) {
	Users::iterator it = _users.find(u);
	if (it == _users.end()) {
		return MemberStatus(MemberStatus::ERROR);
	}
	else {
		return it->second;
	}
}

unsigned int	Channel::userCount() const {
	return _userCount;
}

/**
 * Setters
 */

void	Channel::setName(std::string name) {
	_name = name;
}

void	Channel::setPassword(std::string password) {
	_password = password;
}

/**
 * Methods
 */

void	Channel::addUser(User * u, MemberStatus s /*= MemberStatus(0)*/) {
	_users[u] = s;
	_userCount++;
	u->setChannelCount(u->channelCount() + 1);
}

void	Channel::removeUser(User * u) {
	_users.erase(u);
	_userCount--;
	u->setChannelCount(u->channelCount() - 1);
}

bool	Channel::isUser(User * u) {
	Users::iterator it = _users.find(u);
	if (it == _users.end()) {
		return false;
	}
	else {
		return true;
	}
}

void	Channel::setStatus(User * u, char c) {
	MemberStatus::Status s = MemberStatus::translate(c);
	if (s == MemberStatus::ERROR)
		return;
	Users::iterator it = _users.find(u);
	if (it != _users.end()) {
		it->second.set(s);
	}
}

void	Channel::setStatus(User * u, MemberStatus::Status s) {
	if (s == MemberStatus::ERROR)
		return;
	Users::iterator it = _users.find(u);
	if (it != _users.end()) {
		it->second.set(s);
	}
}

void	Channel::unsetStatus(User * u, char c) {
	MemberStatus::Status s = MemberStatus::translate(c);
	if (s == MemberStatus::ERROR)
		return ;
	Users::iterator it = _users.find(u);
	if (it != _users.end()) {
		it->second.unset(s);
	}
}

void	Channel::unsetStatus(User * u, MemberStatus::Status s) {
	if (s == MemberStatus::ERROR)
		return ;
	Users::iterator it = _users.find(u);
	if (it != _users.end()) {
		it->second.unset(s);
	}
}

bool	Channel::isStatusSet(User * u, char c) {
	MemberStatus::Status s = MemberStatus::translate(c);
	if (s == MemberStatus::ERROR)
		return false;
	Users::iterator it = _users.find(u);
	if (it != _users.end()) {
		return it->second.isSet(s);
	}
	return false;
}

bool	Channel::isStatusSet(User * u, MemberStatus::Status s) {
	if (s == MemberStatus::ERROR)
		return false;
	Users::iterator it = _users.find(u);
	if (it != _users.end()) {
		return it->second.isSet(s);
	}
	return false;
}


void	Channel::setMode(char c) {
	ChannelMode::Mode m = ChannelMode::translate(c);
	if (m == ChannelMode::ERROR)
		return ;
	_mode.set(m);
}

void	Channel::setMode(ChannelMode::Mode m) {
	if (m == ChannelMode::ERROR)
		return ;
	_mode.set(m);
}

void	Channel::unsetMode(char c) {
	ChannelMode::Mode m = ChannelMode::translate(c);
	if (m == ChannelMode::ERROR)
		return ;
	_mode.unset(m);
}

void	Channel::unsetMode(ChannelMode::Mode m) {
	if (m == ChannelMode::ERROR)
		return ;
	_mode.unset(m);
}

bool	Channel::isModeSet(char c) {
	ChannelMode::Mode m = ChannelMode::translate(c);
	if (m == ChannelMode::ERROR)
		return false;
	return _mode.isSet(m);
}

bool	Channel::isModeSet(ChannelMode::Mode m) {
	if (m == ChannelMode::ERROR)
		return false;
	return _mode.isSet(m);
}

void	Channel::send(std::string message, User * sender /* = NULL*/) {
	for (Users::iterator it = users().begin(); it != users().end(); it++) {
		if (sender == NULL || it->first != sender) {
			it->first->send(message);
		}
	}
}
