#include "Parser.hpp"
#include "Command.hpp"
#include <string>
#include <algorithm>

Parser::Parser( std::string input ) : _input(input) {}
Parser::~Parser(){}

std::string	Parser::input() const { return _input; }
void		Parser::setInput( std::string newInput ) { _input = newInput; }

std::string	Parser::output() const { return _output; }
void		Parser::setOutput( std::string newOutput ) { _output = newOutput; }

#include <iostream>

void	Parser::parseInput() {

	size_t index = _input.find_first_not_of(" ");
	if (index == std::string::npos) {
		return;
	}

	size_t nextSpace = _input.find(" ", index);
	if (nextSpace == std::string::npos) {
		nextSpace = _input.size() - 1;
	}

	std::string	toAdd = _input.substr(index, nextSpace - index);
	if (!commandValid(toAdd)) {
		_command.setSyntaxError(true);
		return;
	}
	_command.setCommand(toAdd);
	if (nextSpace >= _input.size()) {
		return;
	}
	index = _input.find_first_not_of(" ", nextSpace);
	while (index < _input.size()) {
		nextSpace = _input.find(" ", index);
		if (_input.at(index) == ':' || nextSpace == std::string::npos) {
			nextSpace = _input.size() - 1;
		}
		if (_input.at(index) != ':') {
			if (index != nextSpace) {
				toAdd = _input.substr(index, nextSpace - index);
				if (std::find(toAdd.begin(), toAdd.end(), '\0') != toAdd.end()) {
					_command.setSyntaxError(true);
					return ;
				}
				_command.addArgument(toAdd);
			}
		}
		else {
			index++;
			if (index < _input.size()) {
				toAdd = _input.substr(index, nextSpace - index);
				if (std::find(toAdd.begin(), toAdd.end(), '\0') != toAdd.end()) {
					_command.setSyntaxError(true);
					return ;
				}
				_command.addArgument(toAdd);
			}
		}
		if (nextSpace >= _input.size()) {
			break;
		}
		index = nextSpace + 1;
	}
}

Command		Parser::command() const { return _command; }

bool	myIsAlpha(char c) {
	return std::isalpha(c);
}

bool	myIsDigit(char c) {
	return std::isdigit(c);
}

bool	Parser::commandValid(std::string command) const {

	if (command.size() == 3 && myAllOf(command.begin(), command.end(), myIsDigit)) {
		return true;
	}
	return myAllOf(command.begin(), command.end(), myIsAlpha);
}
