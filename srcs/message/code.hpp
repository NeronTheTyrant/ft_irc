#ifndef CODE_HPP
# define CODE_HPP

# define CODE_RPL_WELCOME 		1
# define CODE_RPL_YOURHOST 		2
# define CODE_RPL_CREATED 		3
# define CODE_RPL_MYINFO 		4
# define CODE_RPL_UMODEIS		221
# define CODE_RPL_AWAY 			301
# define CODE_RPL_UNAWAY 		305
# define CODE_RPL_NOWAWAY 		306
# define CODE_RPL_WHOISUSER 	311
# define CODE_RPL_WHOISOPERATOR 313
# define CODE_RPL_ENDOFWHO 		315
# define CODE_RPL_WHOISIDLE 	317
# define CODE_RPL_ENDOFWHOIS 	318
# define CODE_RPL_CHANNELMODEIS 324
# define CODE_RPL_NOTOPIC 		331
# define CODE_RPL_TOPIC 		332
# define CODE_RPL_INVITING		341
# define CODE_RPL_NAMREPLY 		353
# define CODE_RPL_ENDOFNAMES 	366
# define CODE_RPL_YOUREOPER 	381

/**
 *  ERRORS
*/
# define CODE_ERR_NOSUCHNICK 		401
# define CODE_ERR_NOSUCHCHANNEL 	403
# define CODE_ERR_CANNOTSENDTOCHAN 	404
# define CODE_ERR_NORECIPIENT 		411
# define CODE_ERR_NOTEXTTOSEND 		412
# define CODE_ERR_UNKNOWNCOMMAND 	421
# define CODE_ERR_NONICKNAMEGIVEN 	431
# define CODE_ERR_ERRONEUSNICKNAME 	432
# define CODE_ERR_NICKNAMEINUSE 	433
# define CODE_ERR_NOTONCHANNEL		442
# define CODE_ERR_USERONCHANNEL		443
# define CODE_ERR_NOTREGISTERED 	451
# define CODE_ERR_NEEDMOREPARAMS 	461
# define CODE_ERR_ALREADYREGISTRED	462
# define CODE_ERR_PASSWDMISMATCH	464
# define CODE_ERR_UNKNOWNMODE		472
# define CODE_ERR_INVITEONLYCHAN	473
# define CODE_ERR_CHANOPRIVSNEEDED	482
# define CODE_ERR_RESTRICTED 		484
# define CODE_ERR_NOOPERHOST 		491
# define CODE_ERR_UMODEUNKNOWNFLAG 	501
# define CODE_ERR_USERSDONTMATCH 	502
#endif
