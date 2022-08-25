#include "IRCServer.hpp"

void	IRCServer::restart(User * user, std::vector<std::string> params) {
	(void)(params);
	if (!user->isRegistered()) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOTREGISTERED, user)));
		return ;
	}
	else if (user->isModeSet(UserMode::OPERATOR) == false) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOPRIVILEGES, user)));
		return ;
	}
	else {
		std::string reason = user->nickname() + " is restarting the server";
		clear(reason);
		_restartFlag = true;
		stop();
	}
}
