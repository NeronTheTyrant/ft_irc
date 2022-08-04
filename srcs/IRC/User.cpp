#include "User.hpp"

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
		case ERROR :
			return '\0';
	}
	return '\0';
}

/**
 * Constructors & Destructors
 */

User::User(int sd, uint32_t requirementFlags) 
	: Client(sd), _requirements(requirementFlags) {
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
	if (this->_hostname != rhs._hostname)
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

std::string	User::hostname() const {
	return (_hostname);
}

UserRequirement &	User::requirements() {
	return _requirements;
}

UserMode &	User::mode() {
	return _mode;
}

bool	User::isRegistered() const {
	return !_requirements.flags();
}

/**
 * Setter
 */
void	User::setUsername(std::string username) {
	_username = username;
}

void	User::setNickname(std::string nickname) {
	_nickname = nickname;
}

/**
 * Methods
 */

void	User::setMode(char c) {
	UserMode::Mode m = UserMode::translate(c);
	if (m != UserMode::ERROR)
		_requirements.set(m);
}

void	User::unsetMode(char c) {
	UserMode::Mode m = UserMode::translate(c);
	if (m != UserMode::ERROR)
		_requirements.unset(m);
}

bool	User::isModeSet(UserMode::Mode m) {
	if (_mode.isSet(m))
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

bool	User::isRequirementSet(UserRequirement::Requirement r) {
	return _requirements.isSet(r);
}
