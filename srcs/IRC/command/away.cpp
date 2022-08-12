#include "IRCServer.hpp"
#include <iostream>

void	IRCServer::away(User * sender, std::vector<std::string> params) {
	if (!sender->isRegistered()) {
		sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOTREGISTERED, sender)));
		return ;
	}
	if (params.size() == 0 && sender->isModeSet('a')) {
		sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_UNAWAY, sender)));
		return ;
	}
	sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_NOWAWAY, sender)));
}
