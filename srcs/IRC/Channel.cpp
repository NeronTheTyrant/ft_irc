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
		case 'i' :
			return INVITEONLY;
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
		case INVITEONLY :
			return 'i';
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

std::string	Channel::topic() const {
	return _topic;
}

std::string	Channel::userNickList() const {
	std::string	ret("");
	Users::const_iterator it = _users.begin();

	for (; it != _users.end(); ++it) {
		if (isStatusSet(it->first, 'o'))
			ret += "@";
		ret += it->first->nickname();
		Users::const_iterator temp = it;
		if (++temp != _users.end())
			ret += " ";
	}
	return ret;
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

Channel::Invitations &	Channel::invitations() {
	return _invitations;
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

void	Channel::setTopic(std::string topic) {
	_topic = topic;
}

/**
 * Methods
 */

void	Channel::addUser(User * u, MemberStatus s /*= MemberStatus(0)*/) {
	_users[u] = s;
	_userCount++;
	u->setChannelCount(u->channelCount() + 1);
	if (_invitations.find(u->nickname()) != _invitations.end()) {
		_invitations.erase(u->nickname());
	}
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

bool	Channel::isStatusSet(User * u, char c) const {
	MemberStatus::Status s = MemberStatus::translate(c);
	if (s == MemberStatus::ERROR)
		return false;
	Users::const_iterator it = _users.find(u);
	if (it != _users.end()) {
		return it->second.isSet(s);
	}
	return false;
}

bool	Channel::isStatusSet(User * u, MemberStatus::Status s) const {
	if (s == MemberStatus::ERROR)
		return false;
	Users::const_iterator it = _users.find(u);
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

bool	Channel::isModeSet(char c) const {
	ChannelMode::Mode m = ChannelMode::translate(c);
	if (m == ChannelMode::ERROR)
		return false;
	return _mode.isSet(m);
}

bool	Channel::isModeSet(ChannelMode::Mode m) const {
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

void	Channel::invite(User * user) {
	_invitations.insert(user->nickname());
}

bool	Channel::isInvited(User * u) {
	Invitations::iterator it = _invitations.find(u->nickname());
	if (it == _invitations.end()) {
		return false;
	}
	else {
		return true;
	}
}
