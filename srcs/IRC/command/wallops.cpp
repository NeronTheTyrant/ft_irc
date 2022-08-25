#include "IRCServer.hpp"

void	IRCServer::wallops(User * user, std::vector<std::string> params) {
	if (!user->isRegistered()) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOTREGISTERED, user)));
		return;
	}
	if (params.size() < 1) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, user, "WALLOPS")));
		return;
	}
	if (user->isModeSet(UserMode::OPERATOR) == false) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOPRIVILEGES, user)));
		return;
	}
	for (Network::Users::const_iterator it = network().users().begin(); it != network().users().end(); it++) {
		User * target = it->second;
		if (target->isModeSet(UserMode::WALLOPS) || target == user) {
			target->send(serverMessageBuilder(*user, "WALLOPS :" + params[0]));
		}
	}
}
