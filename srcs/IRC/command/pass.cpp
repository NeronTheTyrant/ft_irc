# include "messageBuilder.hpp"
# include "IRCServer.hpp"

# define RPLMESSAGE(code) serverMessageBuilder(*this, commandMessageBuilder(code))

void	IRCServer::pass(User * user, std::vector<std::string> params) {
	if (user->isRegistered()) {
		user->send(RPLMESSAGE(CODE_ERR_ALREADYREGISTERED));
		break;
	}
	if (params.empty()) {
		user->send(RPLMESSAGE(CODE_ERR_NEEDMOREPARAMS));
		break;
	}
	if (password().empty() || password() == params[0]) {
		user->unsetRequirement(UserRequirement::PASS);
		break;
	}
	else {
		user->send(RPLMESSAGE(CODE_ERR_PASSWDMISMATCH));
		// add disconnect here probably
		break;
	}
}
