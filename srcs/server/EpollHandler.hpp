#ifndef EPOLLHANDLER_HPP
# define EPOLLHANDLER_HPP
 
# include <vector>
# include <sys/epoll.h>
# include <iostream>
# include "IEventListener.hpp"
# include "ServerSocket.hpp"

class EpollHandler {
public:
	EpollHandler(int16_t port);
	~EpollHandler();

	void	initMasterSocket();
	void	reinitMasterSocket();
	void	run();
	void	stop();
	void	restart();

	void	addEventListener(IEventListener * listener);
	void	removeEventListener(IEventListener * listener);
	void	clearEventListeners();
	void	disconnectClient(int sd, std::string notification, bool notify = false);

private:
	#define MAX_EVENTS	20
	struct epoll_event			_events[MAX_EVENTS];
	std::vector<IEventListener *>	_eventListeners;

	int				_epollfd;
	ServerSocket	_masterSocket;
	bool			_running;

	void	handleListenerActivity();
	void	handleClientActivity(int index);

	void	raiseConnectEvent(int sd);
	void	raiseDisconnectEvent(int sd, std::string notification, bool notify = false);
	void	raiseReceiveEvent(std::string data, int sd);
	void	raiseLoopEndEvent();
};

#endif
