#include "IRCServer.hpp"
#include "User.hpp"

void	IRCServer::mode(User * user, std::vector<std::string> params) {

	if (!user->isRegistered()) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOTREGISTERED, user)));
		return ;
	}
	if (params.size() < 1) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, user, "MODE")));
		return ;
	}
	if (params[0].size() == 0) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOSUCHNICK, user, params[0])));
		return ;
	}

	/*
	**	Channel modes
	*/
	if (params[0].at(0) == '#') {
		user->send("GOT TO HANDLE CHANNEL MODE\r\n");
		Channel	*	channel = network().getChannelByName(params[0]);
		if (channel == u_nullptr) {
			user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOSUCHCHANNEL, user, params[0])));
			return ;
		}
		if (params.size() == 1) {
			user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_CHANNELMODEIS, user, params[0], ChannelMode().channelmodsToString(*channel))));
		}
		else {
			user->send("GOTTA HANDLE MODE SET UNSET");
		}
	}

	/*
	**	User modes
	*/
	else {
		if (network().getUserByName(params[0]) == u_nullptr) {
			user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOSUCHNICK, user, params[0])));
			return ;
		}
		else if (user->nickname() != params[0]) {
			user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_USERSDONTMATCH, user, params[0])));
			return ;
		}
		if (params.size() == 1 || params[1].size() == 0) {
			user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_UMODEIS, user, UserMode::usermodsToString(*user))));
		}
		else {
			bool error = false;
			if (params[1].size() == 1) {
				user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_UMODEIS, user, params[0], UserMode::usermodsToString(*user))));
				return ;
			}
			bool removeMode = false;

			for (std::string::iterator it = params[1].begin(); it != params[1].end(); ++it) {
				char c = *it;

				removeMode = c == '-' ? true :
							 c == '+' ? false :
							 removeMode;
				if (UserMode::translate(c) == UserMode::Mode::ERROR && c != '+' && c != '-') {
					if (!error) {
						error = true;
					}
				}
				else {
					if (removeMode) {
						user->unsetMode(c);
					}
					else {
						user->setMode(c);
					}
				}
			}
			user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_UMODEIS, user, UserMode::usermodsToString(*user))));
			if (error) {
				user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_UMODEUNKNOWNFLAG, user)));
			}
		}
	}

}
