#ifndef USER_HPP
# define USER_HPP

# include <iostream>

class	User {
	private:
		std::string	_username;
		std::string	_nickname;
		std::string	_realname;
		std::string	_hostname;
		int			_mode;
		bool		_is_op;

	public:
		User() {
			_is_op = false;
		};


		/** Getter
		 */
		std::string	getNickname(void) const { return (_nickname); }
		std::string	getUsername(void) const { return (_username); }
		std::string	getRealname(void) const { return (_realname); }
		std::string	getHostname(void) const { return (_hostname); }
		int			getMode(void) const		{ return (_mode); }
		bool		getOp(void) const		{ return (_is_op); }


		/** Setter
		 */
		void	setUsername(std::string username)	{ _username = username; }
		void	setNickname(std::string nickname)	{ _nickname = nickname; }
		void	setOpStatus(bool status)			{ _is_op = status; }


		bool	operator==(User &rhs) {
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

		bool	operator!=(User &rhs) {
			return (!(rhs == *this));
		}

};

#endif
