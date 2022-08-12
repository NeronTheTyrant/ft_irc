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
	target = this->network().getChannelByName(params[1]);
	if (target == u_nullptr) {
		sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOSUCHCHANNEL, sender, params[1])));
		return ;
	}
	else if (target->users().find(sender) == target->users().end()) {
		sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOTONCHANNEL, sender, params[1])));
		return ;
	}
	target->send(serverMessageBuilder(*sender, paramsToString(params)));
	target->removeUser(sender);
	if (target->userCount() == 0) {
		this->network().remove(target);
		delete target;
	}
}
