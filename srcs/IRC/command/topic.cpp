#include "IRCServer.hpp"
#include <iostream>

bool	IRCServer::checkTopicError(User * sender, std::vector<std::string> params) {
	Channel *target;
	if (params.size() < 1) {
		sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, sender, "TOPIC")));
		return true;
	}
	target = this->network().getChannelByName(params[0]);
	if (target == u_nullptr) {
		sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOSUCHCHANNEL, sender, params[0])));
		return true;
	}
	if (target->users().find(sender) == target->users().end()) {
		sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOTONCHANNEL, sender)));
		return true;
	}
	return false;
}

void	IRCServer::topic(User * sender, std::vector<std::string> params) {
	Channel *target;

	if (checkTopicError(sender, params) == true)
		return ;
	target = this->network().getChannelByName(params[0]);
	if (target->isModeSet('t') && params.size() == 1) {
		sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_TOPIC, sender, target->name(), target->topic())));
		return ;
	}
	else if (target->isModeSet('t') == false && params.size() == 1) {
		sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_NOTOPIC, sender, target->name(), target->topic())));
		return ;
	}
	else if (target->isModeSet('t') == true && params.size() == 2 && params[1] == "") {
		sender->send(serverMessageBuilder(*sender, "TOPIC " + params[0] + " :"));
		target->unsetMode('t');
		target->setTopic("");
	}
	else if (params.size() > 1) {
		sender->send(serverMessageBuilder(*sender, "TOPIC " + paramsToString(params, 2)));
		target->setTopic(params[1]);
		if (target->isModeSet('t') == false)
			target->setMode('t');
		return ;
	}
}
