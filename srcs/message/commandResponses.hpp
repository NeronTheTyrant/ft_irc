#ifndef COMMANDRESPONSES_HPP
# define COMMANDRESPONSES_HPP

# define RPL_WELCOME(nick) (":Welcome to the Internet Relay Network " + nick + "\r\n") //1
# define RPL_YOURHOST(servername, version) (":Your host is " + servername + ", running version " + version + "\r\n") //2
# define RPL_CREATED(date) (":This server was created " + date + "\r\n") //3
# define RPL_MYINFO(servername, version, usr_modes, chann_modes) (":" + servername + " " + version + " " + usr_modes + " " + chann_modes + "\r\n") //4
# define RPL_AWAY(pseudo, str) (pseudo + " " + str + "\r\n") //301
# define RPL_UNAWAY() (":You are no longer marked as being away\r\n") //305
# define RPL_NOWAWAY() (":You have been marked as being away\r\n") //306
# define RPL_WHOISUSER(nick, user, host, realname) (nick + " " + user + " " + host + " * :" + realname + "\r\n") //311
# define RPL_WHOISOPERATOR(pseudo) (pseudo + " :is an IRC operator\r\n") //313
# define RPL_ENDOFWHO(name) (name + " :End of WHO list\r\n") //315
# define RPL_WHOISIDLE(pseudo, idle, signon) (pseudo + " " + idle + " " + signon + " :seconds idle, signon time\r\n") //317
# define RPL_ENDOFWHOIS(pseudo) (pseudo + " :End of /WHOIS list\r\n") //318
# define RPL_CHANNELMODEIS(channel, mode, params) (channel + " " + mode + " " + params + "\r\n") //324
# define RPL_NOTOPIC(channel) (channel + " :No topic is set\r\n") //331
# define RPL_TOPIC(channel, topic) (channel + " :" + topic + "\r\n") //332
# define RPL_NAMREPLY(nick, channel, nick_list) (nick + channel + " :" + nick_list + "\r\n") //353
# define RPL_ENDOFNAMES(nick, channel) (nick + " " + channel + " :End of NAMES list\r\n") //366

/**
 *  ERRORS
*/
# define ERR_NOSUCHNICK(nick) (nick + " :No such nick/channel\r\n") //401
# define ERR_CANNOTSENDTOCHAN(channel) (channel + " :Cannot send to channel\r\n") //404
# define ERR_NORECIPIENT(command) (":No recipient given " + command + "\r\n") //411
# define ERR_NOTEXTTOSEND() ":No text to send\r\n" //412
# define ERR_UNKNOWNCOMMAND(command) (command + " :Unknown command\r\n") //421
# define ERR_NONICKNAMEGIVEN() ":No nick given\r\n" //431
# define ERR_ERRONEUSNICKNAME(nick) (nick + " :Erroneous nickname\r\n") //433
# define ERR_NICKNAMEINUSE(nick) (nick + " :Nickname is already in use\r\n") //433
# define ERR_NOTREGISTERED() ":You have not registered\r\n" //451
# define ERR_NEEDMOREPARAMS(command)  (command + " :Not enough parameters\r\n") //461
# define ERR_ALREADYREGISTRED() ":Unauthorized command (already registered)\r\n" //462
# define ERR_PASSWDMISMATCH() (":Password incorrect\r\n") //464
# define ERR_RESTRICTED() (":Your connection is restricted!\r\n") //484
# define ERR_USERSDONTMATCH(nick) (nick + ":Cant change mode for other users") //502


#endif
