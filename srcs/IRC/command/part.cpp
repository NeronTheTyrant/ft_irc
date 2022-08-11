#include "IRCServer.hpp"
#include <iostream>

void	IRCServer::part(User *sender, std::vector<std::string> params) {
	Channel *target;

	target = this->Network().getChannelByName(params[1]);
	if (params.size < 2) {
		sender.send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, sender, "PART")));
		return ;
	}
	if (target == u_nullptr) {
		sender.send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOSUCHCHANNEL, sender, params[1])));
		return ;
	}
	else if (target->users.find(sender) == target->users.end()) {
		sender.send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOTONCHANNEL, sender, params[1])));
		return ;
	}
	target->send(serverMessageBuilder(sender, paramsToString(params)));
	target->removeUser(sender);
	if (target->userCount == 0) {
		this->Network().remove(target);
		delete target;
	}
}
