#ifndef IRCEVENTLISTENER_HPP
#define IRCEVENTLISTENER_HPP

#include "IEventListener.hpp"
#include "IRCServer.hpp"
#include <vector>
#include <iostream>

class IRCServer;

class IRCEventListener : public IEventListener {
public:
	IRCEventListener(IRCServer & server);
	virtual ~IRCEventListener();

	void	onConnect(int sd);
	void	onDisconnect(int sd);
	void	onReceive(std::string data, int sd);

private:
	IRCServer & server;
};

#endif
