#include "sockets/EpollHandler.hpp"
#include "sockets/IRCEventListener.hpp"

int	main (void) {

	IRCServer	server(12345);
	server.start();
}
