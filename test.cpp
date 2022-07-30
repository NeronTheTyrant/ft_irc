#include "Command.hpp"
#include "Parser.hpp"
#include <string>
#include <vector>
#include <iostream>

int main() {

	Command command;

	command.setPrefix("this is prefix");
	command.setCommand("this is command");
	command.addArgument("this is first argument");
	command.addArgument("this is second argument");
	command.addArgument("this is third argument");

	std::vector<std::string> arguments = command.arguments();
	std::vector<std::string>::iterator it = arguments.begin();
	std::cout << command.prefix() << '|' << command.command() << '|';
	for ( ; it != arguments.end() ; ++it ) {
		std::cout << *it;
		if (it != arguments.end() - 1)
			std::cout << '|';
	}
	std::cout << '\n';

	std::cout << "PARSING STRING |" << "           test   input lol    ahahh : azdadk : aaaah ds sldklkfsdl" << "|" << '\n';
	Parser parser("           test   input lol    ahahh : azdadk : aaaah ds sldklkfsdl");
	parser.parseInput();
	command = parser.command();

	arguments = command.arguments();
	it = arguments.begin();
	std::cout << '|' << command.prefix() << '|' << command.command() << '|';
	for ( ; it != arguments.end() ; ++it ) {
		std::cout << *it;
		std::cout << '|';
	}
	std::cout << '\n';

	return 0;
}
