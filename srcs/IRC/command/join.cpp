#include "Network.hpp"
#include "utils.hpp"

void	join(User *sender, vector<std::string> params, IRCServer const &serv) {
	Channel *target;

	if (params.size < 2) {
		sender.send(serverMessageBuilder(serv, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, "JOIN"));
				return ;
	}
	target = serv.network().getChannelByName(params[1]);
	if (target != u_nullptr) {
		target.addUser(sender);
		target.send(serverMessageBuilder(serv, "JOIN #" + params[1]);

	}
}
