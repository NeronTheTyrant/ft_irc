#include "IRCEventListener.hpp"
#include <iostream>

void	IRCEventListener::onConnect(int sd) {
	std::cout << "New user connected: " << sd << std::endl;
}

void	IRCEventListener::onDisconnect(int sd) {
	std::cout << "User disconnected: " << sd << std::endl;
}

void	IRCEventListener::onReceive(std::string data, int sd) {
	std::cout << "Data received from " << sd << ": " << data << std::endl;
}
