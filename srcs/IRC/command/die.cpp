#include "IRCServer.hpp"
#include "Network.hpp"

void	IRCServer::die(User * sender, std::vector<std::string> params) {
	if (!sender->isRegistered()) {
		sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOTREGISTERED, sender)));
		return ;
	}
	else if (sender->isModeSet(UserMode::OPERATOR) == false) {
		sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOPRIVILEGES, sender)));
		return ;
	}
	else {
		Network::Users users = network().users();
		std::string reason = sender->nickname() + " has shutdown the server";
		for (Network::Users::iterator it = users.begin(); it != users.end(); ++it) {
			disconnect(it->second, reason);
		}
		_epollHandler.stop();
	}
	(void)(params);
}
