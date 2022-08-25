# include "messageBuilder.hpp"
# include "IRCServer.hpp"

void	IRCServer::pass(User * user, std::vector<std::string> params) {
	if (user->isRegistered()) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_ALREADYREGISTRED, user)));
		return;
	}
	if (params.empty()) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, user, "PASS")));
		return;
	}
	if (password().empty() || password() == params[0]) {
		user->unsetRequirement(UserRequirement::PASS);
		return;
	}
	else {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_PASSWDMISMATCH, user)));
		disconnect(user, "Wrong Password");
		return;
	}
}
