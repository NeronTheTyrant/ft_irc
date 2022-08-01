#ifndef USER_HPP
# define USER_HPP

# include <iostream>
# include "Client.hpp"

class	User : public Client {
private:
	std::string	_username;
	std::string	_nickname;
	std::string	_realname;
	std::string	_hostname;
	int			_mode;
	bool		_isOp;

public:
	User(int sd);
	~User();

	bool	operator==(User &rhs);
	bool	operator!=(User &rhs);

/**
 * Getters
 */
	std::string	nickname() const;
	std::string	username() const;
	std::string	realname() const;
	std::string	hostname() const;
	int			mode() const;
	bool		isOp() const;

/**
 * Setters
 */
	void	setUsername(std::string username);
	void	setNickname(std::string nickname);
	void	setOpStatus(bool status);

};

#endif
