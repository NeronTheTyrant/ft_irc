#include "utils.hpp"
#include "Network.hpp"

void	privmsgToChannel(User *user, vector<std::string> params, IRCServer const &serv)
{
	Channel channel = serv.network().getChannelByName(params[1]);

	for (channel::Users::iterator it; it != channel._users.end(); ++it)
	{
		if (it->first.nickname != user->nickname)
			it->first.send(serverMessageBuilder(serv, paramsToString(params)));
	}
}

void	privmsgCommand(User *user, vector<std::string> params, IRCServer const &serv)
{
	User *target;

	if (params.size < 3)
	{
		user.send(serverMessageBuilder(serv, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, "PRIMSG")));
		return ;
	}
	if ((serv.network().getChannelByName(params[1])) != u_nullptr)
	{
		privmsgToChannel(user, params, serv);
		return ;
	}
	target = serv.network().getUserByName(params[1])))
	if (target != u_nullptr)
	{
		target.send(serverMessageBuilder(serv, paramsToString(params)));
		if (target
	}
}
