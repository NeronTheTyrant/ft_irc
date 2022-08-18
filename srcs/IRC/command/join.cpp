#include "Network.hpp"
#include "utils.hpp"
#include "IRCServer.hpp"
#include <vector>
#include <iostream>

bool	validChan(std::string chanName) {
	if (chanName[0] != '#')
		return false;
	if (chanName.size() > 50)
		return false;
	if (chanName.find_first_of("\b ,") != std::string::npos)
		return false;
	return true;
}

void	IRCServer::join(User *sender, std::vector<std::string> params) {
	if (!sender->isRegistered()) {
		sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOTREGISTERED, sender)));
		return;
	}
	if (params.size() < 1) {
		sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, sender, "JOIN")));
		return ;
	}
	if (params[0] == "0") {
		std::set<Channel *> channels = sender->channelList();
		for (std::set<Channel *>::iterator it = channels.begin(); it != channels.end(); it++) {
			std::vector<std::string> params;
			params.push_back((*it)->name());
			params.push_back("Leaving");
			part(sender, params);
		}
	}
	else if (params[0].size() == 0) {
		return;
	}
	else {
		std::vector<std::string> channelList = ft_split(params[0], ",");
		for (std::vector<std::string>::iterator it = channelList.begin(); it != channelList.end(); it++) {
			std::cout << *it << "\n";
			if (!validChan(*it)) {
				sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOSUCHCHANNEL, sender, *it)));
				continue;
			}
			Channel *	target = this->network().getChannelByName(*it);
			if (target == u_nullptr) {
				target = new Channel(*it, sender);
				network().add(target);
			}
			else if (target->isUser(sender)) {
				continue;
			}
			else {
				if (!target->isInvited(sender) && target->isModeSet(ChannelMode::INVITEONLY)) {
					sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_INVITEONLYCHAN, sender, *it)));
					continue;
				}
				target->addUser(sender);
			}
			target->send(serverMessageBuilder(*sender, std::string("JOIN ") + target->name()));
			std::vector<std::string>	param;
			param.push_back(*it);
			names(sender, param);
//			sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_NAMREPLY, sender, target->name(), target->userNickList())));
//			sender->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_ENDOFNAMES, sender, target->name())));
		}
	}
}
