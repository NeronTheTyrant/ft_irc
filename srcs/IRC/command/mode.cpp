#include "IRCServer.hpp"
#include "User.hpp"

void	IRCServer::mode(User * user, std::vector<std::string> params) {

	/*
	** Preliminary checks
	*/
	if (!user->isRegistered()) { // Unregistered User
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOTREGISTERED, user)));
		return ;
	}
	if (params.size() < 1) { // Not enough params
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, user, "MODE")));
		return ;
	}
	if (params[0].size() == 0) { // Empty first param (allow the check of the next if)
		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOSUCHNICK, user, params[0])));
		return ;
	}

	/*
	**	Channel modes
	*/
	if (params[0].at(0) == '#') {
		Channel	*	channel = network().getChannelByName(params[0]);

		if (channel == u_nullptr) { // Channel doesn't exist
			user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOSUCHCHANNEL, user, params[0])));
			return ;
		}

		if (params.size() == 1) { // No modstrings given
			user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_CHANNELMODEIS, user, params[0], ChannelMode().channelmodsToString(*channel))));
		}
		else { // Handling modstrings

			if (channel->isStatusSet(user, MemberStatus::Status::OPERATOR) == false && channel->isStatusSet(user, MemberStatus::Status::CREATOR) == false) { // User doesn't have sufficient privileges to modify moddes
				user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_CHANOPRIVSNEEDED, user, params[0])));
			}
			else { // Setting / Unsetting modes
				bool	changeMade = false;
				bool	validMode = false;
				bool 	removeMode = false;
				std::vector<std::string> mods (1, std::string ("+"));
				std::string	arguments;
				std::vector<std::string>::iterator modsIt = mods.begin();
				std::vector<std::string>::iterator currentParam= params.begin() + 2;
				for (std::string::iterator it = params[1].begin(); it != params[1].end(); ++it) {

					char c = *it;

					bool tmp = removeMode;
					removeMode = c == '-' ? true :
								 c == '+' ? false :
								 removeMode;
					if ((c == '+' || c == '-') && tmp != removeMode) {
						if ((*modsIt).size() == 1) {
							*((*modsIt).rbegin()) = c;
						}
						else {
							modsIt = mods.insert(mods.end(), std::string () + c);
						}
					}
					if (MemberStatus::translate(c) != MemberStatus::Status::ERROR) {
						if (validMode == false) {
							validMode = true;
						}
						switch (c) {

							case 'o':
								if (currentParam == params.end()) {
									break;
								}
								if (channel->isUser(network().getUserByName(*currentParam)) == false) {
									user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOSUCHNICK, user, *currentParam)));
								}
								else {
									if (removeMode == true && channel->isStatusSet(network().getUserByName(*currentParam), c) == true) {
										if (changeMade == false) {
											changeMade = true;
										}
										if ((*modsIt).find_first_of(c) == std::string::npos) {
											(*modsIt) += c;
											if (arguments.size() != 0) {
												arguments += ' ';
											}
											arguments += *currentParam;
										}
										channel->unsetStatus(network().getUserByName(*currentParam), c);
									}
									else if (removeMode == false && channel->isStatusSet(network().getUserByName(*currentParam), c) == false) {
										if (changeMade == false) {
											changeMade = true;
										}
										if ((*modsIt).find_first_of(c) == std::string::npos) {
											(*modsIt) += c;
											if (arguments.size() != 0) {
												arguments += ' ';
											}
											arguments += *currentParam;
										}
										channel->setStatus(network().getUserByName(*currentParam), c);
									}
								}
								++currentParam;
								break;

							default:
								break;
						}
					}
					else if (ChannelMode::translate(c) != ChannelMode::Mode::ERROR ) {
						if (validMode == false) {
							validMode = true;
						}
					}
					else if (c != '+' && c != '-') {
						user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_UNKNOWNMODE, user, std::string () + c)));
					}
				} // end of modstrings parsing
				if ( validMode == true && changeMade == false ) {
					user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_CHANNELMODEIS, user, params[0], ChannelMode().channelmodsToString(*channel))));
				}
				else if (changeMade == true) {
					std::string modstring ;
					for (std::vector<std::string>::iterator it = mods.begin() ; it != mods.end() ; ++it) {
						modstring += *it;
					}
					user->send(serverMessageBuilder(*user, "MODE " + params[0] + " " + modstring + " " + arguments));
				}
			}
		}
	}

	/*
	**	User modes
	*/
	else {
		if (network().getUserByName(params[0]) == u_nullptr) {
			user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOSUCHNICK, user, params[0])));
			return ;
		}
		else if (user->nickname() != params[0]) {
			user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_USERSDONTMATCH, user, params[0])));
			return ;
		}
		if (params.size() == 1 || params[1].size() == 0) {
			user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_UMODEIS, user, UserMode::usermodsToString(*user))));
		}
		else {
			bool error = false;
			if (params[1].size() == 1) {
				user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_UMODEIS, user, params[0], UserMode::usermodsToString(*user))));
				return ;
			}
			bool removeMode = false;

			for (std::string::iterator it = params[1].begin(); it != params[1].end(); ++it) {
				char c = *it;

				removeMode = c == '-' ? true :
							 c == '+' ? false :
							 removeMode;
				if (UserMode::translate(c) == UserMode::Mode::ERROR && c != '+' && c != '-') {
					if (!error) {
						error = true;
					}
				}
				else {
					if (removeMode) {
						user->unsetMode(c);
					}
					else {
						user->setMode(c);
					}
				}
			}
			user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_UMODEIS, user, UserMode::usermodsToString(*user))));
			if (error) {
				user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_UMODEUNKNOWNFLAG, user)));
			}
		}
	}
}
