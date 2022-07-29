#include "Channel.hpp"

/**
 * Constructors & Destructors
 */

Channel::Channel(std::string chan_name, User * creator, std::list<User *> operators)
	: _name(chan_name), _opList(operators) {
		_userList.push_back(creator);
		_opList.push_back(creator);
	}

/**
 * Getters
 */

std::string	Channel::name() const {
	return (_name);
}

std::string	Channel::password() const {
	return (_password);
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

bool	Channel::removeUser(std::string nickname) {	
	for (user_iterator it = _userList.begin(); it != _userList.end(); ++it) {
		if ((*it)->nickname() == nickname) {
			_userList.erase(it);
			return (true);
		}
	}
	return (false);
}

bool	Channel::removeOperator(std::string nickname) {
	for (user_iterator it = _opList.begin(); it != _opList.end(); ++it) {
		if ((*it)->nickname() == nickname) {
			_opList.erase(it);
			return (true);
		}
	}
	return (false);
}

bool	removeBanUser() {
	return false;
}


bool	Channel::isUser(User * user) {
	for (user_iterator it = _userList.begin(); it != _userList.end(); ++it) {
		if ((*it)->nickname() == user->nickname())
			return (true);
	}
	return (false);
}

bool	Channel::isOp(User * user) {
	for (user_iterator it = _opList.begin(); it != _opList.end(); ++it) {
		if ((*it)->nickname() == user->nickname())
			return (true);
	}
	return (false);
}

bool	Channel::isBan(User * user) {
	for (user_iterator it = _banList.begin(); it != _banList.end(); ++it) {
		if ((*it)->nickname() == user->nickname())
			return (true);
	}
	return (false);
}
/*
	int	main(void) {
		std::cout << "prout" << std::endl;
}
*/
