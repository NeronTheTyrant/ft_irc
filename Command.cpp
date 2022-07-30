#include <string>
#include <vector>
#include "Command.hpp"

Command::Command(std::string prefix, std::string command, std::vector<std::string> arguments) :
				_prefix(prefix),
				_command(command),
				_arguments(arguments),
				_syntaxError(false) {}
Command::Command(const Command & src) :
				_prefix(src._prefix),
				_command(src._command),
				_arguments(src._arguments),
				_syntaxError(src._syntaxError) {}
Command::~Command() {}

Command &	Command::operator=(const Command & src) {
	if (this != &src) {
		_prefix = src._prefix;
		_command = src._command;
		_arguments = src._arguments;
		_syntaxError = src._syntaxError;
	}
	return *this;
}

void		Command::setPrefix(std::string newPrefix) { _prefix = newPrefix; }
std::string	Command::prefix() const { return _prefix; }

void		Command::setCommand(std::string newCommand) { _command = newCommand; }
std::string	Command::command() const { return _command; }

void						Command::addArgument(std::string argument) { _arguments.push_back(argument); }
std::vector<std::string>	Command::arguments() const{ return _arguments; }

void	Command::setSyntaxError(bool status) { _syntaxError = status; }
bool	Command::syntaxError() const { return _syntaxError; }
