#ifndef USER_HPP
# define USER_HPP

# include <iostream>

class	User
{
	private:
		std::string	_username;
		std::string	_nickname;
		std::string	_realname;
		std::string	_hostname;
		std::string	_password;
		int			_mod;
		bool		_is_op;

	public:
		User()
		{
			_is_op = false;
		};

		void	 setUsername(std::string username)
		{
			_username = username;
		};

		void	setNickname(std::string nickname)
		{
			_nickname = nickname;
		}

		void	setPassword(std::string pass)
		{
			_password = pass;
		}

		void	changeOpStatus(bool status)
		{
			_is_op = status;
		}

		std::string	getNickname(void)	const
		{
			return (_nickname);
		}

		std::string	getUsername(void)	const
		{
			return (_username);
		}

};

#endif
