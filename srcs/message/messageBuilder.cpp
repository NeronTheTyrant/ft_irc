#include "messageBuilder.hpp"

std::string		paramsToString(std::vector<std::string> params, unsigned int n) {
	std::string							ret("");
	std::vector<std::string>::iterator	it = params.begin();
	unsigned int						i = -1;

	while (++i < n && it != params.end())
	{
		ret += *it + " ";
		it++;
	}
	return (ret);
}

std::string		commandMessageBuilder(const	short code, User * user,
		std::string const arg1 , std::string const arg2, std::string const arg3, std::string const arg4) {
	std::string		ret;
	std::string		strCode;

	strCode = ft_itos<short>(code);
	if (code < 10)
		strCode = std::string(2, '0').append(ft_itos<short>(code));
	ret = strCode;
	ret += " ";
	ret += user->nickname();
	ret += " ";
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
		case 221:
			return ret + RPL_UMODEIS(arg1);
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
		case 331:
			return ret + RPL_NOTOPIC(arg1);
		case 332:
			return ret + RPL_TOPIC(arg1, arg2);
		case 353:
			return ret + RPL_NAMREPLY(arg1, arg2);
		case 366:
			return ret + RPL_ENDOFNAMES(arg1);
		case 401:
			return ret + ERR_NOSUCHNICK(arg1);
		case 403:
			return ret + ERR_NOSUCHCHANNEL(arg1);
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
		case 432:
			return ret + ERR_ERRONEUSNICKNAME(arg1);
		case 433:
			return ret + ERR_NICKNAMEINUSE(arg1);
		case 442:
			return ret + ERR_NOTONCHANNEL(arg1);
		case 451:
			return ret + ERR_NOTREGISTERED();
		case 461:
			return ret + ERR_NEEDMOREPARAMS(arg1);
		case 462:
			return ret + ERR_ALREADYREGISTRED();
		case 464:
			return ret + ERR_PASSWDMISMATCH();
		case 472:
			return ret +  ERR_UNKNOWNMODE(arg1);
		case 473:
			return ret + ERR_INVITEONLYCHAN();
		case 482:
			return ret + ERR_CHANOPRIVSNEEDED(arg1);
		case 484:
			return ret + ERR_RESTRICTED();
		case 501:
			return ret + ERR_UMODEUNKNOWNFLAG();
		case 502:
			return ret + ERR_USERSDONTMATCH();
		default:
			return std::string("");
	}
}

std::string		serverMessageBuilder(User & user, std::string content)
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

std::string		serverMessageBuilder(IRCServer & server, std::string content)
{
	std::string message("");

	message += ":" + server.name();
	message += " ";
	message += content;
	message += "\r\n";
	return (message);
}
