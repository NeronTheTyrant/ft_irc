#ifndef IRCEVENTLISTENER_HPP
#define IRCEVENTLISTENER_HPP

#include "IEventListener.hpp"
#include <vector>
#include <iostream>

class IRCEventListener : public IEventListener {

	void	onConnect(int sd);
	void	onDisconnect(int sd);
	void	onReceive(std::string data, int sd);
};

#endif
