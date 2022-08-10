#include "IRCServer.hpp"

int	main (void) {

	IRCServer	server(12345, "chaussette.irc.net", "chaussette");
	server.start();
}
