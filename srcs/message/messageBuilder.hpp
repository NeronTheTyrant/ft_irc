#ifndef MESSAGEBUILDER_HPP
# define MESSAGEBUILDER_HPP

# include <iostream>
# include <map>
# include <vector>

# include "commandResponses.hpp"
# include "code.hpp"
# include "charset.hpp"
# include "utils.hpp"
# include "User.hpp"
# include "IRCServer.hpp"

class IRCServer;
class User;

std::string		commandMessageBuilder(const	short code, std::string const arg1 = std::string(), std::string const arg2 = std::string(), std::string const arg3 = std::string(), std::string const arg4 = std::string());

std::string		serverMessageBuilder(User user, std::string content);
std::string		serverMessageBuilder(IRCServer server, std::string content);

#endif
