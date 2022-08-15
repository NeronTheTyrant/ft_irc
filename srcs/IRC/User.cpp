#include "User.hpp"
#include "utils.hpp"

UserRequirement::UserRequirement(uint32_t flag /*= 0*/)
	: Flag(flag) {}

UserRequirement::~UserRequirement() {}

UserMode::UserMode(uint32_t flag /*= 0*/)
	: Flag(flag) {}

UserMode::~UserMode() {}

UserMode::Mode	UserMode::translate(char c) {
	switch (c) {
		case 'a':
			return AWAY;
		case 'i':
			return INVISIBLE;
		case 'r':
			return RESTRICTED;
		case 'o':
			return OPERATOR;
		case 'w':
			return WALLOPS;
		default:
			return ERROR;
	}
}

char	UserMode::translate(UserMode::Mode m) {
	switch (m) {
		case AWAY :
			return 'a';
		case INVISIBLE :
			return 'i';
		case RESTRICTED :
			return 'r';
		case OPERATOR :
			return 'o';
		case WALLOPS :
			return 'w';
		case ERROR :
			return '\0';
	}
	return '\0';
}

std::string UserMode::usermodsToString(User & user) {

	std::string ret;
	uint32_t i = 1;
	while (i <= 1u << 31 ) {
		if (user.isModeSet(static_cast<UserMode::Mode>(i))) {
			ret += UserMode::translate(static_cast<UserMode::Mode>(i));
		}
		if (i == 1u << 31) {
			break;
		}
		i <<= 1;
	}
	return ret;
}

/**
 * Constructors & Destructors
 */

User::User(int sd, uint32_t requirementFlags)
	: Client(sd), _requirements(requirementFlags), _channelCount(0) {
};


User::~User() {}

/**
 * Operators
 */

bool	User::operator==(User const & rhs) const {
	if (this->_nickname != rhs._nickname)
		return (false);
	if (this->_username != rhs._username)
		return (false);
	if (this->_realname != rhs._realname)
		return (false);
	if (this->hostname() != rhs.hostname())
		return (false);
	return (true);
}

bool	User::operator!=(User const & rhs) const {
	return (!(rhs == *this));
}

/**
 * Getters
 */

std::string	User::nickname() const {
	return (_nickname);
}

std::string	User::username() const {
	return (_username);
}

std::string	User::realname() const {
	return (_realname);
}

std::string	User::awayMessage() const {
	return (_awayMessage);
}

UserRequirement &	User::requirements() {
	return _requirements;
}

UserMode &	User::mode() {
	return _mode;
}

std::map<std::string, Channel *> &	User::channelList(){
	return _channelList;
}

bool	User::isRegistered() const {
	return !_requirements.flags();
//	bool cond = isRequirementSet(UserRequirement::PASS) || isRequirementSet(UserRequirement::USER) || isRequirementSet(UserRequirement::NICK);
//	return !cond;
}

std::string	User::prefix() const {
	return std::string(":") + _nickname + "!" + _username + "@" + hostname();
}

unsigned int	User::channelCount() const {
	return _channelCount;
}

/**
 * Setter
 */
void	User::setUsername(std::string username) {
	_username = username;
}

void	User::setRealname(std::string realname) {
	_realname = realname;
}

void	User::setNickname(std::string nickname) {
	_nickname = nickname;
}

void	User::setAwayMessage(std::string message) {
	_awayMessage = message;
}

void	User::setChannelCount(unsigned int c) {
	_channelCount = c;
}

/**
 * Methods
 */

void	User::setMode(char c) {
	UserMode::Mode m = UserMode::translate(c);
	if (m != UserMode::ERROR)
		_mode.set(m);
}

void	User::setMode(UserMode::Mode m) {
	if (m != UserMode::ERROR)
		_mode.set(m);
}

void	User::unsetMode(char c) {
	UserMode::Mode m = UserMode::translate(c);
	if (m != UserMode::ERROR)
		_mode.unset(m);
}

void	User::unsetMode(UserMode::Mode m) {
	if (m != UserMode::ERROR)
		_mode.set(m);
}

bool	User::isModeSet(char c) const {
	UserMode::Mode m = UserMode::translate(c);
	if (m != UserMode::ERROR && _mode.isSet(m))
		return true;
	else
		return false;
}

bool	User::isModeSet(UserMode::Mode m) const {
	if (m != UserMode::ERROR && _mode.isSet(m))
		return true;
	else
		return false;
}

void	User::setRequirement(UserRequirement::Requirement r) {
	_requirements.set(r);
}

void	User::unsetRequirement(UserRequirement::Requirement r) {
	_requirements.unset(r);
}

bool	User::isRequirementSet(UserRequirement::Requirement r) const {
	return _requirements.isSet(r);
}

void	User::addChannel(Channel *toAdd) {
	if (toAdd != u_nullptr && _channelList.find(toAdd->name()) == _channelList.end()) {
		_channelList[toAdd->name()] = toAdd;
	}
}

bool	User::isRelated(User *toFind) const {
	if (_channelList.size() == 0) {
		return false;
	}
	for (std::map<std::string, Channel *>::const_iterator it = _channelList.begin(); it != _channelList.end(); ++it) {
		if (it->second->isUser(toFind) == true) {
			return true;
		}
	}
	return false;
}
