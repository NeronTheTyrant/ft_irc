#include "IRCServer.hpp"
#include <iostream>

void	IRCServer::away(User * sender, std::vector<std::string> params) {
	if (!sender->isRegistered()) {
		sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOTREGISTERED, sender)));
		return ;
	}
	if (params.size() == 0) {
		if (sender->isModeSet(UserMode::AWAY) == true) {
			sender->unsetMode(UserMode::AWAY);
			sender->setAwayMessage("");
		}
		sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_UNAWAY, sender)));
	}
	else {
		sender->setAwayMessage(params[0]);
		if (sender->isModeSet(UserMode::AWAY) == false) {
			sender->setMode(UserMode::AWAY);
		}
		sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_NOWAWAY, sender)));
	}
}
