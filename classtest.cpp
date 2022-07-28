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
#include <iostream>
#include <vector>

class	SocketTest {
public:
	SocketTest() {
		sd = socket(AF_INET, SOCK_STREAM, 0);
		std::cout << "Socket created: " << sd << std::endl;
	}
	~SocketTest() {
		close(sd);
		std::cout << "Socket closed: " << sd << std::endl;
	}
	int sd;
};

class Wrapper {
public:
	Wrapper() {};
	~Wrapper() {
		std::cout << "wrapper closing" << std::endl;
		std::vector<SocketTest *>::iterator it = sockets.begin();
		for (std::vector<SocketTest *>::iterator ite = sockets.end(); it != ite; it++)
			delete *it;
		sockets.clear();
	}
	std::vector<SocketTest *>	sockets;
	void	add_socket() {
		SocketTest * socket_ptr = new SocketTest();
		sockets.push_back(socket_ptr);
	}
	void	remove_socket() {
		
	}
};



int	main(void) {
	Wrapper	w;
	w.add_socket();
	w.add_socket();
	w.add_socket();
	std::vector<SocketTest *>::iterator ite = w.sockets.end();
	for (std::vector<SocketTest * >::iterator it = w.sockets.begin(); it != ite; it++)
		std::cout << (*it)->sd << std::endl;
r
