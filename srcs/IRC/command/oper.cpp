#include "IRCServer.hpp"
#include "messageBuilder.hpp"
#include <algorithm>

void	IRCServer::oper(User * user, std::vector<std::string> params) {

	if (user->isRegistered() == false) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOTREGISTERED, user)));
		return ;
	}
	else if (params.size() < 2) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, user, "OPER")));
		return ;
	}
	std::map<std::string, std::pair<std::string, std::vector<std::string> > >::const_iterator	opIt = _operatorList.find(params[0]);
	if (opIt == _operatorList.end() || opIt->second.first != params[1]) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_PASSWDMISMATCH, user)));
		return ;
	}
	else if (std::find(opIt->second.second.begin(), opIt->second.second.end(), user->hostname()) == opIt->second.second.end()) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOOPERHOST, user)));
	}
	else if (user->isModeSet('o') == false) {
		user->setMode('o');
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_YOUREOPER, user)));
		user->send(serverMessageBuilder(*this, "MODE " + user->nickname() + " +o"));
	}
}
