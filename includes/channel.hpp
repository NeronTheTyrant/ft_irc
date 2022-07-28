#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "user.hpp"
# include <list>

class Channel
{
	typedef	typename std::list<User*>::iterator			user_iterator;
	typedef	typename std::list<User*>::const_iterator	const_user_iterator;

	private:
		std::string			_chan_name;
		std::string			_password;
		std::list<User*>	_user_list;
		std::list<User*>	_op_list;
		std::list<User*>	_ban_list;

	public:
		Channel(std::string chan_name, User the_maker, std::list<User*> operators)
		{
			_chan_name = chan_name;
			_op_list = operators;
			_user_list.push_back(&the_maker);
		}

		/** Getters
		 */
		std::string	getName(void) const		{ return (_chan_name); }
		std::string	getPassword(void) const	{ return (_password); }


		/** Setters
		 */
		void	setName(std::string name)			{ _chan_name = name; }
		void	setPassword(std::string password)	{ _password = password; }


		/** Methods
		 */
		bool	removeUser(std::string nickname)
		{
			for (user_iterator it = _user_list.begin(); it != _user_list.end(); ++it)
			{
				if ((*it)->getNickname() == nickname)
				{
					_user_list.erase(it);
					return (true);
				}
			}
			return (false);
		}

		bool	removeOperator(std::string nickname)
		{
			for (user_iterator it = _op_list.begin(); it != _op_list.end(); ++it)
			{
				if ((*it)->getNickname() == nickname)
				{
					_op_list.erase(it);
					return (true);
				}
			}
			return (false);
		}

		/**
		 *					/\
		 *				   /  \
		 *				  / !! \
		 *				 /_____ \
		 *	NEED TO FIND A PROPER WAY TO DO THIS.
		 */
		bool	removeBanUser(/* ?????????? */)
		{
			return (false);
		}

		bool	isUser(User user)
		{
			for (user_iterator it = _user_list.begin(); it != _user_list.end(); ++it)
			{
				if ((*it)->getNickname() == user.getNickname())
					return (true);
			}
			return (false);
		}

		bool	isOp(User user)
		{
			for (user_iterator it = _op_list.begin(); it != _op_list.end(); ++it)
			{
				if ((*it)->getNickname() == user.getNickname())
					return (true);
			}
			return (false);
		}

		bool	isBan(User user)
		{
			for (user_iterator it = _ban_list.begin(); it != _ban_list.end(); ++it)
			{
				if ((*it)->getNickname() == user.getNickname())
					return (true);
			}
			return (false);
		}

};

#endif
