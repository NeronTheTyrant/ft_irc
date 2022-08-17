#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>
# include <map>
# include <set>

# include "User.hpp"
# include "Flag.hpp"
# include "utils.hpp"

class Channel;
class User;

class ChannelMode : public Flag {
public:
	enum Mode {
		/* Unknown Mode */
		ERROR = 0,
		/* 'm' - moderated channel */
		MODERATED = 1,
		/* 't' - only channel ops can set topic */
		TOPIC = 1 << 1,
		/* 'i' - invite only */
		INVITEONLY = 1 << 2,
	};

	ChannelMode(uint32_t flag = 0);
	virtual ~ChannelMode();

	static Mode	translate(char c);
	static char	translate(Mode m);
	static std::string channelmodsToString(Channel & channel);
};

class MemberStatus : public Flag {
public:
	enum Status {
		/* Unknown status */
		ERROR = 0,
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
	typedef std::set<std::string>			Invitations;

private:
		std::string			_name;
		std::string			_password;
		std::string			_topic;
		ChannelMode			_mode;
		Users				_users;
		unsigned int		_userCount;
		Invitations			_invitations;

public:
		Channel(std::string name, User * creator);

		/**
		 *	Getters
		 */
		std::string		name() const;
		std::string		password() const;
		std::string		topic() const;
		std::string		userNickList(User *user) const;
		Users &			users();
		MemberStatus	userStatus(User * u);
		unsigned int	userCount() const;
		Invitations &	invitations();

		/**
		 *	Setters
		 */
		void	setName(std::string name);
		void	setTopic(std::string topic);
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

		bool	isStatusSet(User * u, char c) const;
		bool	isStatusSet(User * u, MemberStatus::Status s) const;

		void	setMode(char c);
		void	setMode(ChannelMode::Mode m);

		void	unsetMode(char c);
		void	unsetMode(ChannelMode::Mode m);

		bool	isModeSet(char c) const;
		bool	isModeSet(ChannelMode::Mode m) const;

		void	send(std::string message, User * sender = NULL);
		
		void	invite(User * u);
		bool	isInvited(User * u);

};

#endif

