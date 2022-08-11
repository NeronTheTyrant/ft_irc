#include "Network.hpp"
#include "utils.hpp"
#include "IRCServer.hpp"
#include <vector>
#include <iostream>

void	IRCServer::join(User *sender, vector<std::string> params) {
	Channel *target;

	if (params.size < 2) {
		sender.send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, sender, "JOIN"));
		return ;
	}
	target = this->network().getChannelByName(params[1]);
	if (target != u_nullptr)
		target.addUser(sender);
	else {
		target = new Channel(params[1], sender);
		this->network().add(target);
	}
	target->send(serverMessageBuilder(sender, paramsToString(params));
	sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_NAMREPLY, sender, sender->nickname(), target->name(), target->userNickList()));
	sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_ENDOFNAMES, sender, sender->nickname(), target->name()));
}
