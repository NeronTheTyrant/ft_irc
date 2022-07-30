#include "Parser.hpp"
#include "Command.hpp"
#include <string>

Parser::Parser( std::string input ) : _input(input) {}
Parser::~Parser(){}

std::string	Parser::input() const { return _input; }
void		Parser::setInput( std::string newInput ) { _input = newInput; }

std::string	Parser::output() const { return _output; }
void		Parser::setOutput( std::string newOutput ) { _output = newOutput; }
void	Parser::parseInput() {
	if (_input.size() == 0) {
		_command.setSyntaxError(true);
		return;
	}

	size_t index = 0;
	while (index < _input.size() && _input.at(index) == ' ') {
		index++;
	}

	if (index == _input.size()){
		_command.setSyntaxError(true);
		return;
	}
	size_t nextSpace = _input.find(" ", index);
	if (nextSpace == std::string::npos) {
		nextSpace = _input.size() - 1;
	}
	_command.setCommand(_input.substr(index, nextSpace - index));
	index = nextSpace;
	while (index < _input.size() && _input.at(index) == ' ') {
		index++;
	}
	while (index < _input.size()) {
		nextSpace = _input.find(" ", index);
		if (_input.at(index) == ':' || nextSpace == std::string::npos) {
			nextSpace = _input.size() - 1;
		}
		if (_input.at(index) == ':') {
			index++;
		}
		if (index < _input.size()) {
			_command.addArgument(_input.substr(index, nextSpace - index));
		}
		else {
			_command.addArgument("");
		}
		index = nextSpace + 1;
		while (index < _input.size() && _input.at(index) == ' ') {
			index++;
		}
	}
}
Command	Parser::command() const { return _command; }
