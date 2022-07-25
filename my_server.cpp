#include "sockets/EpollHandler.hpp"
#include "sockets/IRCEventListener.hpp"

int	main (void) {

	EpollHandler	epoll_handler(12345, 3 * 60 * 1000);
	epoll_handler.initMasterSocket();
	IRCEventListener	* irc_event_listener = new IRCEventListener();
	epoll_handler.addEventListener(irc_event_listener);
	epoll_handler.start();
	delete irc_event_listener;
}
