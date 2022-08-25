#include "IRCServer.hpp"
#include <iostream>

void	IRCServer::away(User * sender, std::vector<std::string> params) {
	if (!sender->isRegistered()) {
		sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOTREGISTERED, sender)));
		return ;
	}
	if (params.size() == 0) {
		if (sender->isModeSet(UserMode::Mode::AWAY) == true) {
			sender->unsetMode(UserMode::Mode::AWAY);
			sender->setAwayMessage("");
		}
		sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_UNAWAY, sender)));
	}
	else {
		sender->setAwayMessage(params[0]);
		if (sender->isModeSet(UserMode::Mode::AWAY) == false) {
			sender->setMode(UserMode::Mode::AWAY);
		}
		sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_NOWAWAY, sender)));
	}
}
