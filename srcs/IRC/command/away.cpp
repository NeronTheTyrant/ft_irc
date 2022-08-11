#include "IRCServer.hpp"
#include <iostream>

void	IRCServer::away(User * sender, std::vector<std::string> params) {
	if (params.size() == 0 && sender->isModeSet('a')) {
		sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_UNAWAY, sender)));
		return ;
	}
	sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_NOWAWAY, sender)));
}
