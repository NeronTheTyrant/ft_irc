#include "IRCServer.hpp"
#include <iostream>

bool	checkTopicError(User * sender, std::vector<std::string> params) {
	if (params.size < 2) {
		sender.send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, sender, "TOPIC")));
		return true;
	}
	target = this->Network().getChannelByName(params[1]);
	if (target == u_nullptr) {
		sender.send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOSUCHCHANNEL, sender)));
		return true;
	}
	if (target->users.find(sender) == traget->user.end()) {
		sender.send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOTONCHANNEL, sender)));
		return true;
	}
	return false;
}

void	IRCServer::topic(User * sender, std::vector<std::string> params) {
	Channel *target;

	if (checkTopicError(sender, params) == true)
		return ;
	if (target->isModeSet('t') && params.size == 2) {
		sender.send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_TOPIC, target->name(), target->topic)));
		return ;
	}
	else if (target->isModeSet('t') == false && params.size == 2) {
		sender.send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_NOTOPIC, target->name(), target->topic)));
		return ;
	}
	else if (target->isModeSet('t') == true && params.size == 3 && params[3] == ":") {
		sender.send(serverMessageBuilder(sender, paramsToString(params)));
		target->unsetMode('t');
		target->setTopic("");
	}
	else if (params.size > 2) {
		sender.send(serverMessageBuilder(sender, paramsToString(params)));
		target->setTopic(paramsToString(params + 2));
		if (target->isModeSet('t') == false)
			target->setMode('t');
		return ;
	}
}
