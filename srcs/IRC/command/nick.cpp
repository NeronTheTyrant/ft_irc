#include "../../../includes/commandResponses.hpp"
#include "../../../includes/code.hpp"
#include "../../../includes/charset.hpp"
#include "../../../includes/utils.hpp"
#include "../IRCServer.hpp"
#include "../User.hpp"
#include <vector>
#include <iostream>

void	nickErro(std::string nickname) {
	if (isCharset(nickname[0], SPECIAL) == false
			&& isCharset(nickname[0], LETTER) == false)
		return (
}

void	IRCServer::nick(User & user, std::vector<std::string> params) {
	if (params[0] == "") {
		serverMessageBuilder(user.server, commandMessageBuilder(CODE_ERR_NONICKNAMEGIVEN));
		return ;
	}
	if (network().Users.find(user.nickname()) != network().Users.end()) {
		serverMessageBuilder(user.server, commandMessageBuilder(CODE_ERR_NICKNAMEINUSE));
		return ;
	}
	// NEED A METHOD TO CATCH ERRONEOUS NICKNAME
	if (/*ERRONEOUS FONCTION CHECK*/) {
		serverMessageBuilder(user.server, commandMessageBuilder(CODE_ERR_ERRONEUSNICKNAME));
		return ;
	}
	user.setNickname(params[0]);
}

