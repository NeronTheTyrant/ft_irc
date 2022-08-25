#include "IRCServer.hpp"

void	IRCServer::names(User * user, std::vector<std::string> params) {
	if (!user->isRegistered()) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOTREGISTERED, user)));
		return;
	}
	if (params.size() == 0) {
		for (Network::Channels::iterator it = network().channels().begin(); it != network().channels().end(); it++) {
			Channel * target = it->second;
			user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_NAMREPLY, user, target->name(), target->userNickList(user))));

		}
		std::string visibleNotInChan = network().getVisibleUsersNotInChan(user);
		if (visibleNotInChan.size()) {
			user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_NAMREPLY, user, "*", visibleNotInChan)));
		}
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_ENDOFNAMES, user, "*")));
	}
	else {
	
		std::vector<std::string> channelList = ft_split(params[0], ",");
		for (std::vector<std::string>::iterator it = channelList.begin(); it != channelList.end(); it++) {
			Channel * target = this->network().getChannelByName(*it);
			if (target == u_nullptr) {
			user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_ENDOFNAMES, user, *it)));
				continue ;
			}
			user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_NAMREPLY, user, target->name(), target->userNickList(user))));
			user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_ENDOFNAMES, user, target->name())));
		}
	}
}
