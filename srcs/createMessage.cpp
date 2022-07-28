#include "../includes/commandResponses.hpp"
#include <iostream>

std::string		createMessage(const	short code, std::map<User*>::iterator itUser,
		std::string const arg1, std::string const arg2, std::string const arg3, std::string const arg4) {
	std::string		ret;
	std::string		strCode;
	if (code < 10)
		strCode = std::string(2, '0').append(nbToString);

}
