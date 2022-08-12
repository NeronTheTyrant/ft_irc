#include "Network.hpp"
#include "../../includes/commandResponses.hpp"
#include <vector>
#include <iostream>

void	notice(User *user, vector<std::string> params)
{
	if (!user->isRegistered()) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOTREGISTERED, user)));
		return;
	}
	if (params.size < 3)
	{
		send(serverMessageBuilder(serv, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, sender, "NOTICE"));
		return ;
	}
	if ((serv.network().getChannelByName(params[1])) != u_nullptr)
	{
		user.send(
	}

}
