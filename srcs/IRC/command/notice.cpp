#include "IRCServer.hpp"
#include "commandResponses.hpp"
#include <vector>

void	IRCServer::notice(User *user, std::vector<std::string> params)
{
	if (!user->isRegistered()) {
//		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOTREGISTERED, user)));
		return;
	}
	if (params.size() < 2)
	{
//		send(serverMessageBuilder(serv, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, user, "NOTICE"));
		return ;
	}
	Channel * chan = network().getChannelByName(params[0]);
	if (chan != u_nullptr) {
		if (!chan->isUser(user)) {
//			user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_CANNOTSENDTOCHAN, user, chan->name())));
			return;
		}

		if (chan->isModeSet(ChannelMode::Mode::MODERATED) == false 
			|| chan->isStatusSet(user, MemberStatus::Status::VOICE) == true
			|| chan->isStatusSet(user, MemberStatus::Status::OPERATOR) == true) {
			chan->send(serverMessageBuilder(*user, "NOTICE " + chan->name() + " :" + params[1]));
		}
//		else {
//			user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_CANNOTSENDTOCHAN, user, chan->name())));
//		}
		return ;
	}
	User * target = network().getUserByName(params[0]);
	if (target != u_nullptr) {
//		if (target->isModeSet('a'))
//			user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_AWAY, user, target->nickname(), target->awayMessage())));
		target->send(serverMessageBuilder(*user, "NOTICE " + target->nickname() + " :" + params[1]));
	}
//	else
//		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOSUCHNICK, user, params[0])));

}
