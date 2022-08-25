#include "IRCServer.hpp"
#include <map>
#include <vector>
#include <cstdlib>
#include <errno.h>

int	main (int argc, char **argv) {
	if (argc != 3) {
		std::cout << "Need more arguments" << std::endl;
		return 1;
	}
	char *ptr = NULL;
	errno = 0;
	long int port = strtol(argv[1], &ptr, 10);
	if (*ptr || errno != 0 || port < 1024 || port > 65535) {
		std::cout << argv[1] << " is not a valid port\n";
		return 2;
	}
	std::string password = argv[2];
	IRCServer	server(port, password);
	try {
		server.run();
	}
	catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}
}
