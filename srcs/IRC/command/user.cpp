#include "messageBuilder.hpp"
#include "IRCServer.hpp"
#include <cstdlib>

void	IRCServer::user(User * user, std::vector<std::string> params) {
	if (!user->isRequirementSet(UserRequirement::USER)) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_ALREADYREGISTRED)));
		return;
	}
	if (params.size() < 4) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, "USER")));
		return;
	}
	user->setUsername(params[0]);
	int mode = strtol(params[1].c_str(), NULL, 10);
	if (mode & 1 << 2) {
		user->setMode(UserMode::INVISIBLE);
	}
	if (mode & 1 << 3) {
		user->setMode(UserMode::WALLOPS);
	}
	user->setRealname(params[3]);
	if (user->isRequirementSet(UserRequirement::PASS)) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_PASSWDMISMATCH)));
		disconnect(user, "Bad Password");
		return;
	}
	user->unsetRequirement(UserRequirement::USER);
	if (user->isRegistered()) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_WELCOME, user->nickname())));
	}
}
