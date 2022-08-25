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
		if (chan->isModeSet(ChannelMode::Mode::MODERATED) == false 
			|| chan->isStatusSet(sender, MemberStatus::Status::VOICE) == true
			|| chan->isStatusSet(sender, MemberStatus::Status::OPERATOR) == true) {
			chan->send(serverMessageBuilder(*sender, "PRIVMSG " + chan->name() + " :" + params[1]));
			if (params[1].find("ping") != std::string::npos) {
				std::string pongmsg (params[1]);
				for (size_t pos = pongmsg.find("ping", 0); pos != std::string::npos; pos = pongmsg.find("ping", pos)) {
					pongmsg.replace(pos, 4, "pong");
				}
				chan->send(pongbotmsg("PRIVMSG " + chan->name() + " :" + pongmsg));
			}
			if (params[1].find("pong") != std::string::npos) {
				std::string pingmsg (params[1]);
				for (size_t pos = pingmsg.find("pong", 0); pos != std::string::npos; pos = pingmsg.find("pong", pos)) {
					pingmsg.replace(pos, 4, "ping");
				}
				chan->send(pingbotmsg("PRIVMSG " + chan->name() + " :" + pingmsg));
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
