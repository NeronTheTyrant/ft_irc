#include "IRCServer.hpp"
#include "utils.hpp"
#include <iostream>

void	IRCServer::part(User *sender, std::vector<std::string> params) {
	if (!sender->isRegistered()) {
		sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOTREGISTERED, sender)));
		return ;
	}
	Channel *target;

	if (params.size() < 1) {
		sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, sender, "PART")));
		return ;
	}
	std::vector<std::string> channelList = ft_split(params[0], ",");
	for (std::vector<std::string>::iterator it = channelList.begin(); it != channelList.end(); it++) {
		if (!validChan(*it)) {
			sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOSUCHCHANNEL, sender, *it)));
			continue;
		}
		target = this->network().getChannelByName(*it);
		if (target == u_nullptr) {
			sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOSUCHCHANNEL, sender, *it)));
			continue ;
		}
		else if (!target->isUser(sender)) {
			sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOTONCHANNEL, sender, *it)));
			continue ;
		}
		if (params.size() >= 2) {
			target->send(serverMessageBuilder(*sender, std::string("PART ") + *it + " :" + params[1] + "\r\n"));
		}
		else {
			target->send(serverMessageBuilder(*sender, std::string("PART ") + *it + " :" + sender->nickname() + "\r\n"));
		}
		target->removeUser(sender);
		if (target->userCount() == 0) {
			this->network().remove(target);
		}
	}
}
