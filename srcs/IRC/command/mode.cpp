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

	bool	changeMade = false;
	bool	validMode = false;
	bool 	removeMode = false;
	std::vector<std::string> mods (1, std::string ("+"));
	std::string	arguments;
	std::vector<std::string>::iterator modsIt = mods.begin();
	std::vector<std::string>::iterator currentParam = params.size() >= 2 ?	params.begin() + 2 :
																			params.end();
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
			user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_CHANNELMODEIS, user, channel->name(), ChannelMode::channelmodsToString(*channel))));
		}
		else { // Handling modstrings

			if (channel->isStatusSet(user, MemberStatus::Status::OPERATOR) == false) { // User doesn't have sufficient privileges to modify moddes
				user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_CHANOPRIVSNEEDED, user, channel->name())));
			}
			else { // Setting / Unsetting modes
				for (std::string::iterator it = params[1].begin(); it != params[1].end(); ++it) {

					char c = *it;

					bool tmp = removeMode;
					removeMode = c == '-' ?	true : // set bool in set / unset mode
											c == '+' ?	false :
														removeMode;
					if ((c == '+' || c == '-') && tmp != removeMode) { // if a sign is encountered and set/unset moded changed
						if ((*modsIt).size() == 1) { // if no mode where encountered since the last set/unset changes we just replace the sign
							*((*modsIt).rbegin()) = c;
						}
						else { // we create a new string to concatenate at the end starting with the good sign
							modsIt = mods.insert(mods.end(), std::string () + c);
						}
					}
					if (c == '+' || c == '-') { // no need further processing of the char, we continue the loop
						continue;
					}
					if (MemberStatus::translate(c) != MemberStatus::Status::ERROR) { // mode encountered is a MemberStatus

						if (currentParam == params.end()) { // no param were inputted for this mode, we just ignore it
							continue ;
						}
						if (channel->isUser(network().getUserByName(*currentParam)) == false) { // the param inputted does not fit with a chan member we send the corresponding ERR
							user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOSUCHNICK, user, *currentParam)));
						}
						else { // the mode is valid
							if (validMode == false) {
								validMode = true;
							}
							if (removeMode == true && channel->isStatusSet(network().getUserByName(*currentParam), c) == true) { //currently on unset mode and target's corresponding mode is not set
								if (changeMade == false) { // the mode is gonna make an effective modification
									changeMade = true;
								}
								(*modsIt) += c; // we had c to the output modstring
								if (arguments.size() != 0) { // if an argument were previously added into the output arguments string we add a space
									arguments += ' ';
								}
								arguments += *currentParam; // we add the argument used in the output arguments string
								channel->unsetStatus(network().getUserByName(*currentParam), c); // we finally process the unsetting
							}
							else if (removeMode == false && channel->isStatusSet(network().getUserByName(*currentParam), c) == false) { // same process with set mod
								if (changeMade == false) {
									changeMade = true;
								}
								(*modsIt) += c;
								if (arguments.size() != 0) {
									arguments += ' ';
								}
								arguments += *currentParam;
								channel->setStatus(network().getUserByName(*currentParam), c);
							}
						}
						++currentParam;
					}
					else if (ChannelMode::translate(c) != ChannelMode::Mode::ERROR ) { // if the mode is a ChannelMode
						if (validMode == false) { // as implemented Channel modes don't require arguments we set the validMode directly
							validMode = true;
						}
						if (removeMode == true && channel->isModeSet(c) == true) { // the mode is set and requested to be unset
							if (changeMade == false) { // a change was made
								changeMade = true;
							}
							(*modsIt) += c;
							channel->unsetMode(c); // finally unsetting the mode
						}
						else if (removeMode == false && channel->isModeSet(c) == false) { //same process but mode is unset and need to be set
							if (changeMade == false) {
								changeMade = true;
							}
							(*modsIt) += c;
							channel->setMode(c);
						}
					}
					else { // the modchar given was not valid we send back to the user the corresponding ERR
						user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_UNKNOWNMODE, user, std::string () + c, channel->name())));
					}
				} // end of modstrings parsing
				if ( validMode == true && changeMade == false ) { // at least a valid mode (with valid argument if needed) were inputted but no modification were made, tht mean we need to send a RPL CHANNELMODEIS to the user
					user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_CHANNELMODEIS, user, channel->name(), ChannelMode::channelmodsToString(*channel))));
				}
				else if (changeMade == true) { // at least one modification were made so we send a MODE command to the channel with a modstring and a modstring arguments string corresponding to the effective modification(s)
					std::string modstring ;
					for (std::vector<std::string>::iterator it = mods.begin() ; it != mods.end() ; ++it) {
						modstring += *it;
					}
					channel->send(serverMessageBuilder(*user, "MODE " + channel->name() + " " + modstring + " " + arguments));
				}
			}
		}
	}

	/*
	**	User modes
	*/
	else { // requestion modification(s) on a user (server's scope)
		User * target = network().getUserByName(params[0]);
		if ( target == u_nullptr) { // user doesnt exist, sending the corresponding ERR
			user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_NOSUCHNICK, user, params[0])));
			return ;
		}
		else if (user->nickname() != target->nickname()) { // tried to use mode on another user, sending the corresponing ERR
			user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_USERSDONTMATCH, user, target->nickname())));
			return ;
		}
		if (params.size() == 1 || params[1].size() == 0) { // no modstring were given, sening the UMODEIS RPL
			user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_UMODEIS, user, UserMode::usermodsToString(*user))));
		}
		else { // handling modstring
			bool invalidMode = false;
			for (std::string::iterator it = params[1].begin(); it != params[1].end(); ++it) {

				char c = *it;

				bool tmp = removeMode;
				removeMode = c == '-' ?	true : // set bool in set / unset mode
										c == '+' ?	false :
													removeMode;
				if ((c == '+' || c == '-') && tmp != removeMode) { // if a sign is encountered and set/unset moded changed
					if ((*modsIt).size() == 1) { // if no mode where encountered since the last set/unset changes we just replace the sign
						*((*modsIt).rbegin()) = c;
					}
					else { // we create a new string to concatenate at the end starting with the good sign
						modsIt = mods.insert(mods.end(), std::string () + c);
					}
				}
				if (c == '+' || c == '-') { // no need further processing of the char, we continue the loop
					continue;
				}
				if (UserMode::translate(c) != UserMode::Mode::ERROR) { // mode encountered is a valid UserMode
					if (removeMode == false && c == 'o') {
						continue ;
					}
					if (removeMode == true && user->isModeSet(c) == true) {
						if (changeMade == false) { // a change was made
							changeMade = true;
						}
						(*modsIt) += c;
						user->unsetMode(c);
					}
					else if (removeMode == false && user->isModeSet(c) == false) {
						if (changeMade == false) {
							changeMade = true;
						}
						(*modsIt) += c;
						user->setMode(c);
					}
				}
				else if (invalidMode == false) { // the modchar given was not valid we set the invalidMode flag to true if needed
					invalidMode = true;
				}
			}
			if ( changeMade == false ) { // at least a valid mode (with valid argument if needed) were inputted but no modification were made, tht mean we need to send a RPL CHANNELMODEIS to the user
				user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_RPL_UMODEIS, user, UserMode::usermodsToString(*user))));
			}
			else { // at least one modification were made so we send a MODE command to the channel with a modstring corresponding to the effective modification(s)
				std::string modstring ;
				for (std::vector<std::string>::iterator it = mods.begin() ; it != mods.end() ; ++it) {
					modstring += *it;
				}
				user->send(serverMessageBuilder(*user, "MODE " + target->nickname() + " " + modstring + " "));
			}
			if (invalidMode == true) {
				user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_UMODEUNKNOWNFLAG, user)));
			}
		}
	}
}
