#include "utils.hpp"
#include "Network.hpp"

void	IRCServer::privmsg(User *sender, vector<std::string> params) {
	User	*target;
	Channel	*chan;

	if (params.size < 3) {
		user.send(serverMessageBuilder(this, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, "PRIVMSG")));
		return ;
	}
	chan = serv.network().getChannelByName(params[1]);
	if (chan != u_nullptr) {
		chan.send(serverMessageBuilder(this, paramsToString(params)), sender);
		return ;
	}
	target = serv.network().getUserByName(params[1])))
	if (target != u_nullptr) {
		target.send(serverMessageBuilder(serv, paramsToString(params)));
		if (target.isModeSet('a'))
			sender.send(serv, commandMessageBuilder(CODE_RPL_AWAY, target->getAwayMessage()));
	}
	else
		sender.send(serv, commandMessageBuilder(CODE_ERR_NOSUCHNICK, params[1]);
}
