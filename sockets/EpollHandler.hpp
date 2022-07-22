#include "Sockets.hpp"

/* I want this class to init the server socket by itself, and regularly call
 * accept() and whatever and epoll_ctl to add stuff. I also want to add automated
 * functions for stuff like closing connections. In fact I will have custom event listeners
 * to react to various things, everything will be handled automatically
*/

class EpollHandler {
public:
	EpollHandler(long int timeout)
	~EpollHandler();

	void	initMasterSocket(int16_t port);
	void	start()

private:
	#define MAX_EVENTS	20;
	struct epoll_event			events[MAX_EVENTS];
	std::vector<IEventListener>	event_listeners;

	int				epollfd;
	long int		timeout;
	ServerSocket	master_socket;
	bool			running;

	void	handleListenerActivity();
	void	handleClientActivity(int index);
	void	disconnectClient(int sd);

	void	addEventListener(IEventListener * listener);
	void	removeEventListener(IEventListener * listener);
	void	clearEventListeners();

	void	raiseConnectEvent(int sd);
	void	raiseDisconnectEvent(int sd);
	void	raiseReceiveEvent(std::vector<char> data, sd);
}
