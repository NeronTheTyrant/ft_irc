#include "IRCServer.hpp"

void	IRCServer::quit(User * user, std::vector<std::string> params) {
	if (params.size() >= 1) {
		disconnect(user, params[0]);
	}
	else {
		disconnect(user, "leaving");
	}
}
