# include "messageBuilder.hpp"
# include "IRCServer.hpp"

bool	validNick(std::string nickname) {
	if (isCharset(nickname[0], SPECIAL) == false
			&& isCharset(nickname[0], LETTER) == false)
		return false;
	if (nickname.find_first_not_of(std::string(LETTER) + DIGIT + SPECIAL + "-") != std::string::npos)
		return false;
	return true;
}

void	IRCServer::nick(User * user, std::vector<std::string> params) {
	if (user->isRegistered() && user->isModeSet(UserMode::RESTRICTED)) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_RESTRICTED, user)));
	}
	if (!params.size() || params[0] == "") {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NONICKNAMEGIVEN, user)));
		return ;
	}
	if (!validNick(params[0])) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_ERRONEUSNICKNAME, user, params[0])));
		return ;
	}
	if (network().getUserByName(params[0]) != u_nullptr) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NICKNAMEINUSE, user, params[0])));
		return ;
	}
	std::string message = serverMessageBuilder(*user, std::string("NICK ") + params[0]);
	network().remove(user);
	user->setNickname(params[0]);
	network().add(user);
	if (user->isRequirementSet(UserRequirement::NICK)) {
		if (user->isRequirementSet(UserRequirement::PASS)) {
			user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_PASSWDMISMATCH, user)));
			disconnect(user, "Wrong Password");
			return ;
		}
		user->unsetRequirement(UserRequirement::NICK);
		if (user->isRegistered()) {
			user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_WELCOME, user, user->nickname())));
		}
	}
	else {
		std::list<Channel *> channelList = network().getUserChannelList(user);
		for (std::list<Channel *>::iterator it = channelList.begin(); it != channelList.end(); it++) {
			(*it)->send(message, user);
		}
	}
}

