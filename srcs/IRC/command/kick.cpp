#include "IRCServer.hpp"
#include "utils.hpp"
#include <vector>
#include <iostream>

void	IRCServer::kick(User * user, std::vector<std::string> params) {
	if (!user->isRegistered()) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOTREGISTERED, user)));
		return;
	}
	if (params.size() < 2) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, user, "KICK")));
		return;
	}
	std::vector<std::string>	channels = ft_split(params[0], ",");
	std::vector<std::string>	users = ft_split(params[1], ",");
	std::string reason = (params.size() >= 3) ? params[2] : user->nickname();
	if (channels.size() == 1) {
		Channel * chan = network().getChannelByName(channels[0]);
		if (chan == u_nullptr) {
			user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOSUCHCHANNEL, user, channels[0])));
			return;
		}
		if (!chan->isUser(user)) {
			user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOTONCHANNEL, user, channels[0])));
			return ;
		}
		if (!chan->isStatusSet(user, MemberStatus::OPERATOR)) {
			user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_CHANOPRIVSNEEDED, user, channels[0])));
			return ;
		}
		for (std::vector<std::string>::iterator it = users.begin(); it != users.end(); it++) {
			User * target = network().getUserByName(*it);
			if (!chan->isUser(target)) {
				user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_USERNOTINCHANNEL, user, *it, channels[0])));
				continue;
			}
			chan->send(serverMessageBuilder(*user, std::string("KICK ") + *it + " :" + reason));
			chan->removeUser(target);
		}
		if (chan->userCount() == 0) {
			network().remove(chan);
		}
	}
	else {
		if (channels.size() != users.size()) {
			user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, user, "KICK")));
			return;
		}
		for (unsigned int index = 0; index != channels.size(); index++) {
			Channel * chan = network().getChannelByName(channels[index]);
			if (chan == u_nullptr) {
				user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOSUCHCHANNEL, user, channels[index])));
				continue ;
			}
			if (!chan->isUser(user)) {
				user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOTONCHANNEL, user, channels[index])));
				continue ;
			}
			if (!chan->isStatusSet(user, MemberStatus::OPERATOR)) {
				user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_CHANOPRIVSNEEDED, user, channels[index])));
				continue ;
			}
			User * target = network().getUserByName(users[index]);
			if (!chan->isUser(target)) {
				user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_USERNOTINCHANNEL, user, users[index], channels[index])));
				continue ;
			}
			chan->send(serverMessageBuilder(*user, std::string("KICK ") + users[index] + " :" + reason));
			chan->removeUser(target);
			if (chan->userCount() == 0) {
				network().remove(chan);
			}
		}
	}
}
