#ifndef IEVENTLISTENER_HPP
#define IEVENTLISTENER_HPP

#include <iostream>

class	IEventListener {
public:
	virtual void	onConnect(int sd) = 0;
	virtual void	onDisconnect(int sd, std::string notification) = 0;
	virtual void	onReceive(std::string data, int sd) = 0;
};
#endif
