#include "utils.hpp"
#include "Network.hpp"

void	privmsgCommand(User *sender, vector<std::string> params, IRCServer const &serv) {
	User	*target;
	Channel	*chan;

	if (params.size < 3) {
		user.send(serverMessageBuilder(serv, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, "PRIMSG")));
		return ;
	}
	chan = serv.network().getChannelByName(params[1]);
	if (chan != u_nullptr) {
		chan.send(serverMessageBuilder(serv, paramsToString(params)), sender);
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
