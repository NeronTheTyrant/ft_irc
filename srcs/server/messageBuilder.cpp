#include "../../includes/commandResponses.hpp"
#include "../../includes/utils.hpp"
#include "../IRC/User.hpp"
#include <iostream>
#include <map>

std::string		commandMessageBuilder(const	short code,
		std::string const arg1, std::string const arg2, std::string const arg3, std::string const arg4) {
	std::string		ret;
	std::string		strCode;

	strCode = ft_itos(code);
	if (code < 10)
		strCode = std::string(2, '0').append(ft_itos(code));
	switch (code)
	{
		case 1:
			return ret + RPL_WELCOME(arg1);
		case 2:
			return ret + RPL_YOURHOST(arg1, arg2);
		case 3:
			return ret + RPL_CREATED(arg1);
		case 4:
			return ret + RPL_MYINFO(arg1, arg2, arg3, arg4);
		case 301:
			return ret + RPL_AWAY(arg1, arg2);
		case 305:
			return ret + RPL_UNAWAY();
		case 306:
			return ret + RPL_NOWAWAY();
		case 311:
			return ret + RPL_WHOISUSER(arg1, arg2, arg3, arg4);
		case 313:
			return ret + RPL_WHOISOPERATOR(arg1);
		case 315:
			return ret + RPL_ENDOFWHO(arg1);
		case 317:
			return ret + RPL_WHOISIDLE(arg1, arg2, arg3);
		case 318:
			return ret + RPL_ENDOFWHOIS(arg1);
		case 324:
			return ret + RPL_CHANNELMODEIS(arg1, arg2, arg3);
		case 366:
			return ret + RPL_ENDOFNAMES(arg1);
		case 401:
			return ret + ERR_NOSUCHNICK(arg1);
		case 404:
			return ret + ERR_CANNOTSENDTOCHAN(arg1);
		case 411:
			return ret + ERR_NORECIPIENT(arg1);
		case 412:
			return ret + ERR_NOTEXTTOSEND();
		case 421:
			return ret + ERR_UNKNOWNCOMMAND(arg1);
		case 431:
			return ret + ERR_NONICKNAMEGIVEN();
		case 433:
			return ret + ERR_NICKNAMEINUSE(arg1);
		case 451:
			return ret + ERR_NOTREGISTERED();
		case 461:
			return ret + ERR_NEEDMOREPARAMS(arg1);
		default:
			return std::string("");
	}
}

std::string		serverMessageBuilder(User user, std::string content)
{
	std::string message("");

	message += ":" + user.nickname();
	message += "!" + user.username();
	message += "@" + user.hostname();
	message += " ";
	message += content;
	message += "\r\n";
	return (message);
}
