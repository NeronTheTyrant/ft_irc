#include "IRCEventListener.hpp"
#include <iostream>

void	IRCEventListener::onConnect(int sd) {
	std::cout << "New user connected: " << sd << std::endl;
	DataSocket *	dsock = new DataSocket(sd);
	Client *		client = new Client(dsock);
	User *			user = new User(client);
	server.network().add(user);
}

void	IRCEventListener::onDisconnect(int sd) {
	std::cout << "User disconnected: " << sd << std::endl;
	// insert disconnection using IRCServer::disconnect method here
}

void	IRCEventListener::onReceive(std::string data, int sd) {
	std::cout << "Data received from " << sd << ": " << data << std::endl;
	User * user = server.network().getUserBySocketDescriptor(sd);
	user->client->receive(data);
}
