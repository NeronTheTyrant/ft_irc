#include "messageBuilder.hpp"
#include "IRCServer.hpp"
#include <cstdlib>
#include "Motd.hpp"

void	IRCServer::user(User * user, std::vector<std::string> params) {
	if (!user->isRequirementSet(UserRequirement::USER)) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_ALREADYREGISTRED, user)));
		return;
	}
	if (params.size() < 4) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, user, "USER")));
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
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_PASSWDMISMATCH, user)));
		disconnect(user, "Bad Password");
		return;
	}
	user->unsetRequirement(UserRequirement::USER);
	if (user->isRegistered()) {
		Motd	motd;
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_WELCOME, user, user->nickname())));
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_YOURHOST, user, this->name(), "v1.337")));
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_CREATED, user, this->creationTime())));
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_MYINFO, user, this->name(), "v1.337", "aiow", "ov mtinc")));
		motd.sendMotd(user, this);
	}
}
