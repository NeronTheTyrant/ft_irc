#include "IRCServer.hpp"

void	IRCServer::mode(User * user, std::vector<std::string> params) {

	if (!user->isRegistered()) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOTREGISTERED)));
		return ;
	}
	if (params.size() < 1) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, "MODE")));
		return ;
	}
	if (params[0].size() == 0) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOSUCHNICK, params[0])));
		return ;
	}
	if (params[0].at(0) == '#') {
		user->send("GOT TO HANDLE CHANNEL MODE\r\n");
	}
	else {
		user->send("GOT TO HANDLE USER MODE\r\n");
		if (network().getUserByName(params[0]) == u_nullptr) {
			user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOSUCHNICK, params[0])));
			return ;
		}
		else if (user->nickname() != params[0]) {
			user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_USERSDONTMATCH, params[0])));
			return ;
		}
		if (params.size() == 1) {
			user->send("WITHOUT MODESTRING\r\n");
		}
		else {
			user->send("WITH MODESTRING(S)\r\n");
		}
	}

}
