#include "utils.hpp"
#include "IRCServer.hpp"

void	IRCsigHandler(int sig) {
	if (sig == SIGINT) {
		//do stuff
		free_from_signal(u_nullptr);
	//	exit(SIGINT);
	}
}

