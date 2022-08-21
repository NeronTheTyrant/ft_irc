#ifndef EPOLLHANDLER_HPP
# define EPOLLHANDLER_HPP
 
# include <vector>
# include <sys/epoll.h>
# include <iostream>
# include "IEventListener.hpp"
# include "ServerSocket.hpp"

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
	void	stop();

	void	addEventListener(IEventListener * listener);
	void	removeEventListener(IEventListener * listener);
	void	clearEventListeners();
	void	disconnectClient(int sd, std::string notification);

private:
	#define MAX_EVENTS	20
	struct epoll_event			events[MAX_EVENTS];
	std::vector<IEventListener *>	event_listeners;

	int				epollfd;
	ServerSocket	master_socket;
	bool			_running;

	void	handleListenerActivity();
	void	handleClientActivity(int index);

	void	raiseConnectEvent(int sd);
	void	raiseDisconnectEvent(int sd, std::string notification);
	void	raiseReceiveEvent(std::string data, int sd);
	void	raiseLoopEndEvent();
};

#endif
