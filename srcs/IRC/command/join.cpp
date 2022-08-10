#include "Network.hpp"
#include "utils.hpp"
#include "IRCServer.hpp"
#include <vector>
#include <iostream>

void	IRCServer::join(User *sender, vector<std::string> params, IRCServer const &serv) {
	Channel *target;

	if (params.size < 2) {
		sender.send(serverMessageBuilder(serv, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, "JOIN"));
		return ;
	}
	target = serv.network().getChannelByName(params[1]);
	if (target != u_nullptr)
		target.addUser(sender);
	else {
		target = new Channel(params[1], sender);
		this->network().add(target);
	}
	target.send(serverMessageBuilder(sender, paramsToString(params));
	target.send(serverMessageBuilder(this, commandMessageBuilder(CODE_RPL_NAMREPLY, sender->nickname(), target->name(), target->userNickList()));
	target.send(serverMessageBuilder(this, commandMessageBuilder(CODE_RPL_ENDOFNAMES, sender->nickname(), target->name()));
}
