#include "IRCServer.hpp"
#include "Motd.hpp"
#include "messageBuilder.hpp"
#include "utils.hpp"

#include <iostream>
void	IRCServer::motd(User * sender, std::vector<std::string> params) {
	if (!sender->isRegistered()) {
		sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOTREGISTERED, sender)));
		return ;
	}
	if (params.size() > 0 && strToUpper(params[0]) != strToUpper(_name)) {
		sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOSUCHSERVER, sender, params[0])));
	}
	else {
		Motd motd;
		motd.sendMotd(sender, this);
	}
}
