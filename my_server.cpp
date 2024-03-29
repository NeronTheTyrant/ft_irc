#include "IRCServer.hpp"
#include <map>
#include <vector>
#include <cstdlib>
#include <errno.h>

int	main (int argc, char **argv) {
	try {
		if (argc < 3) {
			std::cout << "Need more arguments" << std::endl;
			return 1;
		}
		else if ( argc > 3) {
			std::cout << "Need only 3 arguments" << std::endl;
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
		server.run();
		return 0;
	}
	catch (std::exception & e) {
		std::cout << "there" << std::endl;
		std::cout << e.what() << std::endl;
		return 1;
	}
}
