# include "messageBuilder.hpp"
# include "IRCServer.hpp"

#define RPLMESSAGE(code) serverMessageBuilder(*this, commandMessageBuilder(code))

bool	validNick(std::string nickname) {
	if (isCharset(nickname[0], SPECIAL) == false
			&& isCharset(nickname[0], LETTER) == false)
		return false;
	if (nickname.find_first_not_of(std::string(LETTER) + DIGIT + SPECIAL + "-") == std::string::npos)
		return false;
	return true;
}

void	IRCServer::nick(User * user, std::vector<std::string> params) {
	if (user->isRegistered() && user->isModeSet(UserMode::RESTRICTED)) {
		user->send(RPLMESSAGE(CODE_ERR_RESTRICTED));
	}
	if (params[0] == "") {
		user->send(RPLMESSAGE(CODE_ERR_NONICKNAMEGIVEN));
		return ;
	}
	if (!validNick(params[0])) {
		user->send(RPLMESSAGE(CODE_ERR_ERRONEUSNICKNAME));
		return ;
	}
	if (network().getUserByName(user->nickname())) {
		user->send(RPLMESSAGE(CODE_ERR_NICKNAMEINUSE));
		return ;
	}
	std::string message = serverMessageBuilder(*user, std::string("NICK ") + params[0]); 
	network().remove(user);
	user->setNickname(params[0]);
	network().add(user);
	if (user->isRequirementSet(UserRequirement::NICK)) {
		user->unsetRequirement(UserRequirement::NICK);
		if (user->isRegistered()) {
			user->send(RPLMESSAGE(CODE_RPL_WELCOME));
		}
	}
	else {
		std::list<Channel *> channelList = network().getUserChannelList(user);
		for (std::list<Channel *>::iterator it = channelList.begin(); it != channelList.end(); it++) {
			(*it)->send(message);
		}
	}
}

