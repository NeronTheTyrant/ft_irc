#include "utils.hpp"
#include "IRCServer.hpp"

void	IRCsigHandler(int sig) {
	if (sig == SIGINT || sig == SIGHUP || sig == SIGQUIT) {
		//do stuff
		free_from_signal(u_nullptr);
	//	exit(SIGINT);
	}
}

