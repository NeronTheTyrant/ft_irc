#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define TRUE             1
#define FALSE            0

typedef struct client {
	public:
		struct pollfd	fd;
		std::string		stock;
}	client;

int	main (int argc, char **argv) {
	unsigned int		port = 12345;
	int			ret;
	struct pollfd		listener;
	std::list<client>	clist;

	/* Get listener socket */
	listener.fd = socket(AF_LOCAL, SOCK_STREAM, 0);
	if (listener.fd < 0) {
		perror("socket() failed");
		exit(-1);
	}
	
	/* Allow socket descriptor to be reusable */
	int opt = 1;
	ret = setsockopt(listener.fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
	if (ret < 0) {
		perror ("setsockopt() failed");
		close(listener.fd);
		exit(-1);
	}

	/* Set listener to be nonblocking */
	ret = fcntl(listener.fd, F_SETFL, opt | O_NONBLOCK);
	if (ret < 0) {
		perror("fcntl() failed");
		close(listener.fd);
		exit(-1);
	}

	/* Bind listener socket */
	struct sockaddr_in	serv_addr;
	serv_addr.sin_family = AF_LOCAL;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);
	ret = bind(listener.fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if (ret < 0) {
		perror("bind() failed"):
		close(listener.fd);
		exit(-1);
	}

	/* Set listening backlog */
	ret = listen(listener.fd, 32);
	if (ret < 0) {
		perror("listen() failed");
		close(listener.fd);
		exit(-1);
	}
	
	/* Set up listening socket events */
	listener.events = POLLIN;

	/* timeout = 3 minutes */
	long unsigned int timetout = 3 * 60 * 1000;

	/* Loop through listener and clients */
	while (TRUE) {
		/* Call poll

}
