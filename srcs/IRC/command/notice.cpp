#include "IRCServer.hpp"
#include "commandResponses.hpp"
#include <vector>

void	IRCServer::notice(User *user, std::vector<std::string> params)
{
	if (!user->isRegistered()) {
		return;
	}
	if (params.size() < 2)
	{
		return ;
	}
	Channel * chan = network().getChannelByName(params[0]);
	if (chan != u_nullptr) {
		if (chan->isModeSet(ChannelMode::NOEXTERN) && !chan->isUser(user)) {
			return;
		}
		if (chan->isModeSet(ChannelMode::Mode::MODERATED) == false 
			|| chan->isStatusSet(user, MemberStatus::Status::VOICE) == true
			|| chan->isStatusSet(user, MemberStatus::Status::OPERATOR) == true) {
			chan->send(serverMessageBuilder(*user, "NOTICE " + chan->name() + " :" + params[1]));
		}
		return ;
	}
	User * target = network().getUserByName(params[0]);
	if (target != u_nullptr) {
		target->send(serverMessageBuilder(*user, "NOTICE " + target->nickname() + " :" + params[1]));
	}

}
