#ifndef IRCEVENTLISTENER_HPP
#define IRCEVENTLISTENER_HPP

#include "IEventListener.hpp"
#include <vector>
#include <iostream>

class IRCEventListener : public IEventListener {
public:
	void	onConnect(int sd);
	void	onDisconnect(int sd);
	void	onReceive(std::string data, int sd);

private:
	IRCServer & server;
};

#endif
