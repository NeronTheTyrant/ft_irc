#ifndef COMMANDRESPONSES_HPP
# define COMMANDRESPONSES_HPP

# define RPL_WELCOME(nick) (":Welcome to the Internet Relay Network " + nick + "\r\n") //1
# define RPL_YOURHOST(servername, version) (":Your host is " + servername + ", running version " + version + "\r\n") //2
# define RPL_CREATED(date) (":This server was created " + date + "\r\n") //3
# define RPL_MYINFO(servername, version, usr_modes, chann_modes) (":" + servername + " " + version + " " + usr_modes + " " + chann_modes + "\r\n") //4
# define RPL_CHANNELMODEIS(channel, mode, mode_params) (channel + " " + mode + " " + mode_params + "\r\n" //324
# define RPL_NOTOPIC(channel) (channel + " :No topic is set\r\n") //331
# define RPL_TOPIC(channel, topic) (channel + " :" + topic + "\r\n") //332
# define RPL_NAMREPLY(channel, nick_list) (channel + " :" + nick_list + "\r\n") //353
# define RPL_ENDOFNAMES(channel) (channel + " :End of NAMES list\r\n") //366

/**
 *  ERRORS
*/

# define ERR_NOSUCHNICK(nick) (nick + " :No such nick/channel\r\n") //401
# define ERR_CANNOTSENDTOCHAN(channel) (channel + " :Cannot send to channel\r\n") //404
# define ERR_NORECIPIENT(command) (":No recipient given " + command + "\r\n") //411
# define ERR_NOTEXTTOSEND ":No text tosend\r\n" //412
# define ERR_UNKNOWNCOMMAND(command) (command + " :Unknown command\r\n") //421
# define ERR_NONICKNAMEGIVEN ":No nick given\r\n" //431
# define ERR_NICKNAMEINUSE(nick) (nick + " :Nickname is already in use\r\n" //433
# define ERR_NOTREGISTERED ":You have not registered\r\n" //451
# define ERR_NEEDMOREPARAMS(command)  (command + " :Not enough parameters\r\n") //461
# define ERR_ALREADYREGISTRED ":Unauthorized command (already registered)\r\n" //462
# define ERR_PASSWDMISMATCH() (":Password incorrect\r\n") //464


#endif
