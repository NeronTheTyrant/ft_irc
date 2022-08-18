#include "IRCServer.hpp"
#include "utils.hpp"
#include <vector>
#include <iostream>

void	IRCServer::list(User * user, std::vector<std::string> params) {
	if (!user->isRegistered()) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOTREGISTERED, user)));
		return;
	}
	if (params.size() == 0) {
		for (Network::Channels::iterator it = network().channels().begin(); it != network().channels().end(); it++) {
			Channel * target = it->second;
			user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_LIST, user, target->name(), ft_itos<unsigned int>(target->nbVisible(user)), target->topic())));
		}
	}
	else {
		std::vector<std::string> channelList = ft_split(params[0], ",");
		for (std::vector<std::string>::iterator it = channelList.begin(); it != channelList.end(); it++) {
			Channel * target = network().getChannelByName(*it);
			if (target == u_nullptr) {
				continue;
			}
			user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_LIST, user, target->name(), ft_itos<unsigned int>(target->nbVisible(user)), target->topic())));
		}
	}
	user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_LISTEND, user)));
}
