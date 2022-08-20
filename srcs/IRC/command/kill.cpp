#include "IRCServer.hpp"
#include "messageBuilder.hpp"

void	IRCServer::kill(User * user, std::vector<std::string> params) {

	if (user->isRegistered() == false) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOTREGISTERED, user)));
		return ;
	}
	else if (user->isModeSet(UserMode::OPERATOR) == false) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOPRIVILEGES, user)));
		return ;
	}
	else if (params.size() < 2) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, user, "KILL")));
		return ;
	}
	User * target = network().getUserByName(params[0]);
	if (target == u_nullptr) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOSUCHNICK, user, params[0])));
		return ;
	}
	else {
		target->send(serverMessageBuilder(*user, "KILL " + target->nickname() + ' ' + params[1]));
		std::string reason = "Killed (" + user->nickname() + " (" + params[1] + "))";
		disconnect(target, reason);
	}
}
