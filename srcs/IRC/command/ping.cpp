#include "IRCServer.hpp"

void	IRCServer::ping(User * user, std::vector<std::string> params) {
	if (!user->isRegistered()) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOTREGISTERED, user)));
		return;
	}
	if (params.size() < 1) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, user, "USER")));
		return;
	}
	user->send(serverMessageBuilder(*this, "PONG " + _name + " " + params[0]));
}
