#ifndef EPOLLHANDLER_HPP
#define EPOLLHANDLER_HPP

#include "Sockets.hpp"
#include <vector>
#include <sys/epoll.h>
#include "IEventListener.hpp"
#include <iostream>

/* I want this class to init the server socket by itself, and regularly call
 * accept() and whatever and epoll_ctl to add stuff. I also want to add automated
 * functions for stuff like closing connections. In fact I will have custom event listeners
 * to react to various things, everything will be handled automatically
*/

class EpollHandler {
public:
	EpollHandler(int16_t port);
	~EpollHandler();

	void	initMasterSocket();
	void	run();

	void	addEventListener(IEventListener * listener);
	void	removeEventListener(IEventListener * listener);
	void	clearEventListeners();

private:
	#define MAX_EVENTS	20
	struct epoll_event			events[MAX_EVENTS];
	std::vector<IEventListener *>	event_listeners;

	int				epollfd;
	ServerSocket	master_socket;
	bool			running;

	void	handleListenerActivity();
	void	handleClientActivity(int index);
	void	disconnectClient(int sd);

	void	raiseConnectEvent(int sd);
	void	raiseDisconnectEvent(int sd);
	void	raiseReceiveEvent(std::string data, int sd);
};

#endif
