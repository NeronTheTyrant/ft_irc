#include "utils.hpp"
#include "Network.hpp"
#include "IRCServer.hpp"
#include <vector>
#include <iostream>

void	IRCServer::privmsg(User *sender, std::vector<std::string> params) {
	User	*target;
	Channel	*chan;

	if (params.size() < 2) {
		sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, sender, "PRIVMSG")));
		return ;
	}
	chan = network().getChannelByName(params[0]);
	if (chan != u_nullptr) {
		chan->send(serverMessageBuilder(*sender, paramsToString(params)), sender);
		return ;
	}
	target = network().getUserByName(params[0]);
	if (target != u_nullptr) {
		if (target->isModeSet('a'))
			sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_AWAY, target, target->awayMessage())));
		target->send(serverMessageBuilder(*sender, paramsToString(params)));
	}
	else
		sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOSUCHNICK, sender, params[0])));
}
