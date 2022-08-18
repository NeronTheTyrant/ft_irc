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

std::string ChannelMode::channelmodsToString(Channel & channel) {

	std::string ret;
	uint32_t i = 1;
	while (i <= 1u << 31 ) {
		if (channel.isModeSet(static_cast<ChannelMode::Mode>(i))) {
			ret += ChannelMode::translate(static_cast<ChannelMode::Mode>(i));
		}
		if (i == 1u << 31) {
			break;
		}
		i <<= 1;
	}
	return ret;
}

MemberStatus::MemberStatus(uint32_t flag)
	: Flag(flag) {}

MemberStatus::~MemberStatus() {}

MemberStatus::Status	MemberStatus::translate(char c) {
	switch (c) {
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
	addUser(creator, MemberStatus(MemberStatus::OPERATOR));
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

std::string	Channel::userNickList(User *user) const {
	std::string	ret("");
	Users::const_iterator it = _users.begin();

	bool firstPrint = true;
	for (; it != _users.end(); ++it) {
		if (it->first->isModeSet(UserMode::Mode::INVISIBLE) == false || user->isRelated(it->first)) {
			if (firstPrint == true) {
				firstPrint = false;
			}
			else {
				ret += ' ';
			}
			if (isStatusSet(it->first, 'o'))
				ret += '@';
			else if (isStatusSet(it->first, 'v')) {
				ret += '+';
			}
			ret += it->first->nickname();
		}
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

unsigned int	Channel::nbVisible(User * u) {
	unsigned int ret = 0;
	for (Users::iterator it = _users.begin(); it != _users.end(); ++it) {
		if (it->first->isModeSet(UserMode::Mode::INVISIBLE) == false || u->isRelated(it->first)) {
			ret++;
		}
	}
	return ret;
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
	u->addChannel(this);
	if (_invitations.find(u->nickname()) != _invitations.end()) {
		_invitations.erase(u->nickname());
	}
}

void	Channel::removeUser(User * u) {
	u->removeChannel(this);
	_users.erase(u);
	_userCount--;
	u->setChannelCount(u->channelCount() - 1);
}

void	Channel::clearUsers() {
	for (Users::iterator it = users().begin(); it != users().end(); it++) {
		removeUser(it->first);
	}
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
	_invitations.insert(strToUpper(user->nickname()));
}

bool	Channel::isInvited(User * u) {
	Invitations::iterator it = _invitations.find(strToUpper(u->nickname()));
	if (it == _invitations.end()) {
		return false;
	}
	else {
		return true;
	}
}
