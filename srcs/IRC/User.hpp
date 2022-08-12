#ifndef USER_HPP
# define USER_HPP

# include <iostream>
# include "Client.hpp"
# include "Flag.hpp"

class User;

class UserRequirement: public Flag {
public:
	enum Requirement {
		PASS = 1,
		NICK = 1 << 1,
		USER = 1 << 2,
		SKIP_PASS = NICK | USER,
		ALL = PASS | NICK | USER
	};

	UserRequirement(uint32_t flag = 0);
	virtual ~UserRequirement();
};

class UserMode: public Flag {
public:
	enum Mode {
		ERROR = 0,
		/* 'a' - User is away */
		AWAY = 1,
		/* 'i' - User is invisible */
		INVISIBLE = 1 << 1,
		/* 'r' - User has a restricted connection */
		RESTRICTED = 1 << 2,
		/* 'o' - User has operator privileges */
		OPERATOR = 1 << 3,
		/* 'w' - User receives wallops (see WALLOPS command) */
		WALLOPS = 1 << 4
	};

	UserMode(uint32_t flag = 0);
	virtual ~UserMode();

	static Mode	translate(char c);
	static char	translate(Mode m);
	static std::string usermodsToString(User & user);
};

class	User : public Client {
private:
	std::string			_username;
	std::string			_nickname;
	std::string			_realname;
	std::string			_awayMessage;
	UserRequirement		_requirements;
	UserMode			_mode;
	unsigned int		_channelCount;

public:
	User(int sd, uint32_t requirementFlags);
	~User();

	bool	operator==(User const & rhs) const;
	bool	operator!=(User const & rhs) const;

/**
 * Getters
 */
	std::string			nickname() const;
	std::string			username() const;
	std::string			realname() const;
	std::string			awayMessage() const;
	UserRequirement &	requirements();
	UserMode &			mode();
	bool				isRegistered() const;
	std::string			prefix() const;
	unsigned int		channelCount() const;

/**
 * Setters
 */
	void	setUsername(std::string username);
	void	setRealname(std::string realname);
	void	setNickname(std::string nickname);
	void	setAwayMessage(std::string message);
	void	setChannelCount(unsigned int c);

/**
 * Methods
 */
	void	setMode(char c);
	void	setMode(UserMode::Mode m);

	void	unsetMode(char c);
	void	unsetMode(UserMode::Mode m);

	bool	isModeSet(char c) const;
	bool	isModeSet(UserMode::Mode m) const;

	void	setRequirement(UserRequirement::Requirement r);
	void	unsetRequirement(UserRequirement::Requirement r);
	bool	isRequirementSet(UserRequirement::Requirement r) const;

};

#endif
