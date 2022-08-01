#include "IRCEventListener.hpp"
#include <iostream>

IRCEventListener::IRCEventListener(IRCServer & server)
	: server(server) {}

IRCEventListener::~IRCEventListener() {}

void	IRCEventListener::onConnect(int sd) {
	std::cout << "New user connected: " << sd << std::endl;
	User *			user = new User(sd);
	server.network().add(user);
}

void	IRCEventListener::onDisconnect(int sd) {
	std::cout << "User disconnected: " << sd << std::endl;
	User * user = server.network().getUserBySocket(sd);
	server.network().remove(user);
	delete user;
	// insert disconnection using IRCServer::disconnect method here
}

void	IRCEventListener::onReceive(std::string data, int sd) {
	std::cout << "Data received from " << sd << ": " << data << std::endl;
	User * user = server.network().getUserBySocket(sd);
	user->receive(data);
	while (user->crlf()) {
		std::string line = user->line();
		std::cout << line << std::endl;
		user->clearLine();
		//parse(line);
		//createMessage(line);
		//executeCommand(line);
		//other stuff
		user->send(line);
	}
}
