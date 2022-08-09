#include "messageBuilder.hpp"
#include "IRCServer.cpp"
#include <cstdlib>

#define RPLMESSAGE(code) serverMessageBuilder(*this, commandMessageBuilder(code))

void	IRCServer::user(User * user, std::vector<std::string> params) {
	if (user->isRequirementSet(UserRequirement::USER) {
		user->send(RPLMESSAGE(CODE_ERR_ALREADYREGISTERED));
		break;
	}
	if (params.size() < 4) {
		user->send(RPLSMESSAGE(CODE_ERR_NEEDMOREPARAMS));
		break;
	}
	user->set
		
}
