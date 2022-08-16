#include "IRCServer.hpp"
#include "messageBuilder.hpp"

void	IRCServer::invite(User * user, std::vector<std::string> params) {
	if (!user->isRegistered()) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOTREGISTERED, user)));
		return;
	}
	if (params.size() < 2) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, user, "INVITE")));
		return;
	}
	User * invitee = network().getUserByName(params[0]);
	if (invitee == u_nullptr) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOSUCHNICK, user, params[0])));
		return;
	}
	Channel * target = network().getChannelByName(params[1]);
	if (target == u_nullptr) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOSUCHCHANNEL, user, params[1])));
		return;
	}
	if (!target->isUser(user)) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOTONCHANNEL, user, params[1])));
		return;
	}
	if (target->isUser(invitee)) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_USERONCHANNEL, user, params[0], params[1])));
		return;
	}
	if (target->isModeSet(ChannelMode::INVITEONLY) && !target->isStatusSet(user, MemberStatus::OPERATOR)) {
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_CHANOPRIVSNEEDED, user, params[1])));
		return;
	}
	target->invite(invitee);
	invitee->send(serverMessageBuilder(*user, std::string("INVITE ") + paramsToString(params, 2)));
	user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_INVITING, user, params[0], params[1])));
}
