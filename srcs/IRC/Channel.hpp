#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "User.hpp"
# include <list>
# include <iostream>
# include <string>

class Channel {
public:
	typedef	typename std::list<User*>::iterator			user_iterator;
	typedef	typename std::list<User*>::const_iterator	const_user_iterator;

private:
		std::string			_name;
		std::string			_password;
		std::list<User*>	_userList;
		std::list<User*>	_opList;

public:
		Channel(std::string chan_name, User * creator, std::list<User*> operators);

		/**
		 *	Getters
		 */
		std::string	name() const;
		std::string	password() const;

		/**
		 *	Setters
		 */
		void	setName(std::string name);
		void	setPassword(std::string password);

		/**
		 *	Methods
		 */
		bool	removeUser(std::string nickname);
		bool	removeOperator(std::string nickname);

		bool	isUser(User * user);
		bool	isOp(User * user);

};

#endif

