#include "Command.hpp"
#include "Parser.hpp"
#include "IRCEventListener.hpp"
#include <iostream>

IRCEventListener::IRCEventListener(IRCServer & server)
	: server(server) {}

IRCEventListener::~IRCEventListener() {}

void	IRCEventListener::onConnect(int sd) {
	std::cout << "New user connected: " << sd << '\n';
	User *	user = new User(sd, UserRequirement::ALL);
	server.network().add(user);
}

void	IRCEventListener::onDisconnect(int sd) {
	std::cout << "User disconnected: " << sd << '\n';
	User * user = server.network().getUserBySocket(sd);
	server.network().remove(user);
	delete user;
	// insert disconnection using IRCServer::disconnect method here
}

void	IRCEventListener::onReceive(std::string data, int sd) {
	std::cout << "Data received from " << sd << ": " << data << '\n';
	User * user = server.network().getUserBySocket(sd);
	user->receive(data);
	while (user->crlf()) {
		std::string line = user->line();
		std::cout << line << '\n';
		user->clearLine();

		Parser	lineParser (line);
		lineParser.parseInput();

		Command command = lineParser.command();
		std::vector<std::string>	arguments = command.arguments();

		if (command.syntaxError() == true)
			std::cout << "SYNTAX ERROR" << '\n';
		std::cout << "|Prefix|\n|Command|\n#0|Argument 0|\n#1|Argument1|\n...\n" << '\n';
		std::cout << '|' << command.prefix() << "|" << '\n';
		std::cout << '|' << command.command() << "|" << '\n';
		size_t	i = 0;
		for ( std::vector<std::string>::iterator it = arguments.begin() ; it != arguments.end() ; ++it, ++i) {
			std::cout << '#' << i << '|' << *it << "|" << '\n';
		}
		//parse(line);
		//createMessage(line);
		//executeCommand(line);
		//other stuff
		user->send(line);
	}
}
