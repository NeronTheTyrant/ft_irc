#include "Command.hpp"
#include "Parser.hpp"
#include "IRCEventListener.hpp"
#include <iostream>

IRCEventListener::IRCEventListener(IRCServer & server)
	: server(server) {}

IRCEventListener::~IRCEventListener() {}

void	IRCEventListener::onConnect(int sd) {
	User *	user = new User(sd, UserRequirement::ALL);
	server.network().add(user);
}

void	IRCEventListener::onDisconnect(int sd, std::string notification, bool notify) {
	User * user = server.network().getUserBySocket(sd);
	if (user == u_nullptr) {
		return;
	}
	server.clearUser(user, notification, notify);
	server.addToRemoveList(user);
	user->setQuit(true);
}

void	IRCEventListener::onReceive(std::string data, int sd) {
	User * user = server.network().getUserBySocket(sd);
	user->receive(data);
	while (user->crlf()) {
		std::string line = user->line();
		user->clearLine();

		Parser	lineParser (line);
		lineParser.parseInput();

		Command command = lineParser.command();
		if (command.syntaxError() == true) {
			continue ;
		}
		server.execCommand(user, command);
		if (user->quit()) {
			break;
		}
	}
}

void	IRCEventListener::onLoopEnd() {
	server.clearRemoveList();
}

