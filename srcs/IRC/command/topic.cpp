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
	if (!sender->isRegistered()) {
		sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOTREGISTERED, sender)));
		return ;
	}
	Channel *target;

	if (checkTopicError(sender, params) == true)
		return ;
	target = this->network().getChannelByName(params[0]);
	if (params.size() == 1 && target->topic().size() > 0) {
		sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_TOPIC, sender, target->name(), target->topic())));
		return ;
	}
	else if (params.size() == 1) {
		sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_NOTOPIC, sender, target->name(), target->topic())));
		return ;
	}
	else if (target->isModeSet('t') == true && target->isStatusSet(sender, MemberStatus::OPERATOR) == false) {
		sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_CHANOPRIVSNEEDED, sender, target->name())));
		return ;
	}
	else {
		target->send(serverMessageBuilder(*sender, "TOPIC " + paramsToString(params, 2)));
		target->setTopic(params[1]);
		return ;
	}
}
