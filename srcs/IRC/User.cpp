#include "User.hpp"

/**
 * Constructors & Destructors
 */

User::User(int sd) 
	: Client(sd) {
	_isOp = false;
};


User::~User() {}

/**
 * Operators
 */

bool	User::operator==(User &rhs) {
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

bool	User::operator!=(User &rhs) {
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

int	User::mode() const {
	return (_mode);
}

bool		User::isOp() const {
	return (_isOp);
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

void	User::setOpStatus(bool status) {
	_isOp = status;
}

/**
 * Methods
 */

