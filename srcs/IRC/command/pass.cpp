# include "messageBuilder.hpp"
# include "IRCServer.hpp"

void	IRCServer::pass(User * user, std::vector<std::string> params) {
	if (user->isRegistered()) {
		user->send(RPLMESSAGE(CODE_ERR_ALREADYREGISTRED));
		return;
	}
	if (params.empty()) {
		user->send(RPLMESSAGE(CODE_ERR_NEEDMOREPARAMS));
		return;
	}
	if (password().empty() || password() == params[0]) {
		user->unsetRequirement(UserRequirement::PASS);
		return;
	}
	else {
		user->send(RPLMESSAGE(CODE_ERR_PASSWDMISMATCH));
		disconnect(user, "Wrong Password");
		return;
	}
}
