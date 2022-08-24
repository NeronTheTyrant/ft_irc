#include "IRCServer.hpp"
#include <map>
#include <vector>
#include <cstdlib>

int	main (int argc, char **argv) {
	if (argc != 3) {
		std::cout << "Need more arguments" << std::endl;
		return 1;
	}
	long int port = strtol(argv[1], NULL, 10);
	// des check
	std::string password = argv[2];
	// des check
	IRCServer	server(port, password);
	server.run();
}
