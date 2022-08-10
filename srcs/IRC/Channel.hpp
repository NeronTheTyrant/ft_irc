#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>
# include <map>

# include "User.hpp"
# include "Flag.hpp"

class ChannelMode : public Flag {
public:
	enum Mode {
		/* Unknown Mode */
		ERROR = 0,
		/* 'm' - moderated channel */
		MODERATED = 1,
		/* 't' - only channel creator can set topic */
		TOPIC = 1 << 1,
	};

	ChannelMode(uint32_t flag = 0);
	virtual ~ChannelMode();

	static Mode	translate(char c);
	static char	translate(Mode m);
};

class MemberStatus : public Flag {
public:
	enum Status {
		/* Unknown status */
		ERROR = 0,
		/* 'O' - channel creator */
		CREATOR = 1,
		/* 'o' - channel operator */
		OPERATOR = 1 << 1,
		/* 'v' - member can speak in moderated or restricted channel */
		VOICE = 1 << 2,
	};

	MemberStatus(uint32_t flag = 0);
	virtual ~MemberStatus();

	static Status translate(char c);
	static char translate(Status s);
};


class Channel {
public:
	typedef std::map<User *, MemberStatus>	Users;

private:
		std::string			_name;
		std::string			_password;
		ChannelMode			_mode;
		Users				_users;
		unsigned int		_userCount;

public:
		Channel(std::string name, User * creator);

		/**
		 *	Getters
		 */
		std::string		name() const;
		std::string		password() const;
		Users &			users();
		MemberStatus	userStatus(User * u);
		unsigned int	userCount() const;

		/**
		 *	Setters
		 */
		void	setName(std::string name);
		void	setPassword(std::string password);

		/**
		 *	Methods
		 */
		void	addUser(User * u, MemberStatus s = MemberStatus(0));
		void	removeUser(User * u);
		bool	isUser(User * u);

		void	setStatus(User * u, char c);
		void	setStatus(User * u, MemberStatus::Status s);

		void	unsetStatus(User * u, char c);
		void	unsetStatus(User *u, MemberStatus::Status s);

		bool	isStatusSet(User * u, char c);
		bool	isStatusSet(User * u, MemberStatus::Status s);

		void	setMode(char c);
		void	setMode(ChannelMode::Mode m);
				
		void	unsetMode(char c);
		void	unsetMode(ChannelMode::Mode m);

		bool	isModeSet(char c);
		bool	isModeSet(ChannelMode::Mode m);

		void	send(std::string message, User * sender = NULL);

};

#endif

