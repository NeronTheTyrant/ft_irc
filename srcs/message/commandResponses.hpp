#ifndef COMMANDRESPONSES_HPP
# define COMMANDRESPONSES_HPP

# define RPL_WELCOME(nick) (":Welcome to the Internet Relay Network " + nick)										//1
# define RPL_YOURHOST(servername, version) (":Your host is " + servername + ", running version " + version) 		//2
# define RPL_CREATED(date) (":This server was created " + date)														//3
# define RPL_MYINFO(servername, version, usr_modes, chann_modes) (":" + servername + " " + version + " " + usr_modes + " " + chann_modes) //4
# define RPL_UMODEIS(modes) ("+" + modes)																			//221
# define RPL_AWAY(pseudo, str) (pseudo + " :" + str)																//301
# define RPL_UNAWAY() (":You are no longer marked as being away")													//305
# define RPL_NOWAWAY() (":You have been marked as being away")														//306
# define RPL_WHOISUSER(nick, user, host, realname) (nick + " " + user + " " + host + " * :" + realname) 			//311
# define RPL_WHOISOPERATOR(pseudo) (pseudo + " :is an IRC operator")												//313
# define RPL_ENDOFWHO(name) (name + " :End of WHO list")															//315
# define RPL_WHOISIDLE(pseudo, idle, signon) (pseudo + " " + idle + " " + signon + " :seconds idle, signon time")	//317
# define RPL_ENDOFWHOIS(pseudo) (pseudo + " :End of /WHOIS list")													//318
# define RPL_LIST(channel, visiblenb, topic) (channel + " " + visiblenb + " :" + topic)								//322
# define RPL_LISTEND() (":End of LIST")																				//323	
# define RPL_CHANNELMODEIS(channel, mode, params) (channel + " +" + mode + " " + params)							//324
# define RPL_NOTOPIC(channel) (channel + " :No topic is set")														//331
# define RPL_TOPIC(channel, topic) (channel + " :" + topic)															//332
# define RPL_INVITING(nick, channel) (nick + " " + channel)															//341
# define RPL_NAMREPLY(channel, nick_list) ("= " + channel + " :" + nick_list)										//353
# define RPL_ENDOFNAMES(channel) (channel + " :End of NAMES list")													//366
# define RPL_YOUREOPER() (" :You are now an IRC Operator")															//381

/**
 *  ERRORS
*/
# define ERR_NOSUCHNICK(nick) (nick + " :No such nick/channel")														//401
# define ERR_NOSUCHCHANNEL(channel) (channel + " :No such channel")													//403
# define ERR_CANNOTSENDTOCHAN(channel) (channel + " :Cannot send to channel")										//404
# define ERR_NORECIPIENT(command) (":No recipient given " + command)												//411
# define ERR_NOTEXTTOSEND() ":No text to send"																		//412
# define ERR_UNKNOWNCOMMAND(command) (command + " :Unknown command")												//421
# define ERR_NONICKNAMEGIVEN() ":No nick given"																		//431
# define ERR_ERRONEUSNICKNAME(nick) (nick + " :Erroneous nickname")													//433
# define ERR_NICKNAMEINUSE(nick) (nick + " :Nickname is already in use")											//433
# define ERR_NOTONCHANNEL(channel) (channel + " :You're not on that channel");										//442
# define ERR_USERONCHANNEL(user, channel) (user + " " + channel + " :is already on channel")						//443
# define ERR_NOTREGISTERED() ":You have not registered"																//451
# define ERR_NEEDMOREPARAMS(command)  (command + " :Not enough parameters")											//461
# define ERR_ALREADYREGISTRED() ":Unauthorized command (already registered)"										//462
# define ERR_PASSWDMISMATCH() (":Password incorrect")																//464
# define ERR_UNKNOWNMODE(c, channel) (c + " :is unknown mode char to me for " + channel)							//472
# define ERR_INVITEONLYCHAN(channel) (channel + ":Cannot join channel (+i)")										//473
# define ERR_NOPRIVILEGES() (":Permission Denied- You're not an IRC operator")										//481
# define ERR_CHANOPRIVSNEEDED(channel) (channel + ":You're not channel operator")									//482
# define ERR_RESTRICTED() (":Your connection is restricted!")														//484
# define ERR_NOOPERHOST() (":No 0-lines for your host")																//491
# define ERR_UMODEUNKNOWNFLAG() (":Unknown MODE flag")																//501
# define ERR_USERSDONTMATCH(nick) (nick + ":Cant change mode for other users")										//502


#endif
