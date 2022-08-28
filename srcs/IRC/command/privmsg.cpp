#include "utils.hpp"
#include "Network.hpp"
#include "IRCServer.hpp"
#include <vector>
#include <iostream>

void	IRCServer::privmsg(User *sender, std::vector<std::string> params) {
	if (!sender->isRegistered()) {
		sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOTREGISTERED, sender)));
		return;
	}
	User	*target;
	Channel	*chan;

	if (params.size() < 2) {
		sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, sender, "PRIVMSG")));
		return ;
	}
	chan = network().getChannelByName(params[0]);
	if (chan != u_nullptr) {
		if (chan->isModeSet(ChannelMode::NOEXTERN) && !chan->isUser(sender)) {
			sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_CANNOTSENDTOCHAN, sender, chan->name())));
			return;
		}
		if (chan->isModeSet(ChannelMode::MODERATED) == false 
			|| chan->isStatusSet(sender, MemberStatus::VOICE) == true
			|| chan->isStatusSet(sender, MemberStatus::OPERATOR) == true) {
			chan->send(serverMessageBuilder(*sender, "PRIVMSG " + chan->name() + " :" + params[1]), sender);
			if (chan->isModeSet(ChannelMode::CHATBOT)) {
				if (params[1].find("ping") != std::string::npos) {
					std::string pongmsg = strReplaceAll(params[1], "ping", "pong");
					chan->send(botmsg("pongbot", "PRIVMSG " + chan->name() + " :" + pongmsg));
				}
				if (params[1].find("pong") != std::string::npos) {
					std::string pingmsg = strReplaceAll(params[1], "pong", "ping");
					chan->send(botmsg("pingbot", "PRIVMSG " + chan->name() + " :" + pingmsg));
				}
			}
		}
		else {
			sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_CANNOTSENDTOCHAN, sender, chan->name())));
		}
		return ;
	}
	target = network().getUserByName(params[0]);
	if (target != u_nullptr) {
		if (target->isModeSet('a'))
			sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_AWAY, sender, target->nickname(), target->awayMessage())));
		target->send(serverMessageBuilder(*sender, "PRIVMSG " + target->nickname() + " :" + params[1]));
	}
	else
		sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOSUCHNICK, sender, params[0])));
}
