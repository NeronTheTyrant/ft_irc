#include "EpollHandler.hpp"
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdexcept>

EpollHandler::EpollHandler(int16_t port)
	: epollfd(-1), master_socket(port) {};

EpollHandler::~EpollHandler() {
	if (epollfd > 0)
		close(epollfd);
}

void	EpollHandler::initMasterSocket() {
	try {
		master_socket.init();
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}

void	EpollHandler::run() {
	// if master_socket is not set
	if (master_socket.getsd() == -1)
		throw std::logic_error("EpollHandler: Master socket initialised with invalid socket descriptor");

	// start listening for new connections
	master_socket.start();

	// init epoll instance
	epollfd = epoll_create1(0);
	if (epollfd < 0)
		throw std::runtime_error("Could not create epoll instance");

	// set master socket events
	struct epoll_event	ev;
	ev.data.fd = master_socket.getsd();
	ev.events = EPOLLIN | EPOLLPRI | EPOLLERR | EPOLLHUP;

	// add master socket to epoll interest list
	int ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, master_socket.getsd(), &ev);
	if (ret < 0)
		throw std::runtime_error("Could not add master socket to epoll interest list");

	// event loop
	running = 1;
	while (running) {

		// check for new events
		int nfds = epoll_wait(epollfd, events, MAX_EVENTS, 60 * 3 * 1000);
		if (nfds == -1)
			throw std::runtime_error("epoll_wait() failed to wait for events");

		for (int n = 0; n < nfds; n++) {
			if (events[n].data.fd == master_socket.getsd())
				handleListenerActivity();
			else
				handleClientActivity(n);
		}
	}
}


// function called when epoll signals an event on master_socket / listener

void	EpollHandler::handleListenerActivity() {

	// TODO add epoll event error handler?? Maybe an extra function

	// user ServerSocket wrapper to accept connection
	int	sd = master_socket.accept();

	// add possible events to new client sd
	struct epoll_event	ev;
	ev.data.fd = sd;
	ev.events = EPOLLIN;

	// add new client to epoll interest list
	int ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, sd, &ev);
	if (ret < 0)
		throw std::runtime_error("Could not add master socket to epoll interest list");

	raiseConnectEvent(sd);
}

// function called when epoll signals an event on client socket

void	EpollHandler::handleClientActivity(int index) {

	if (events[index].events & EPOLLIN) {
		std::cout << "Client activity!!" << std::endl;

		//if file descriptor is invalid
		if (events[index].data.fd < 0)
			throw std::logic_error("Invalid client file descriptor");

		// Read data from socket
		char buffer[512] = {0};
		int	received = recv(events[index].data.fd, buffer, sizeof(buffer), 0);
		std::cout << received << std::endl;

		if (received < 0) {
			if (errno != EAGAIN && errno != EWOULDBLOCK) {
				close(events[index].data.fd);
				throw std::runtime_error("recv() failed");
			}
		}
		else if (received == 0) { // Connection was closed remotey
			disconnectClient(events[index].data.fd);
			raiseDisconnectEvent(sd);
		}
		else {
			std::string	data(buffer);
			raiseReceiveEvent(data, events[index].data.fd);
			if (data == "close\n") {
				epoll_ctl(epollfd, EPOLL_CTL_DEL, events[index].data.fd, NULL);
				close(events[index].data.fd);
			}
		}
	}
	if (events[index].events & EPOLLOUT) {
		// ToDo Implement
		std::cout << "EPOLLOUT" << std::endl;
	}
	if (events[index].events & EPOLLRDHUP) {
		// ToDo Implement
		std::cout << "EPOLLRDHUP" << std::endl;
	}
	if (events[index].events & EPOLLHUP) {
		// ToDo Implement
		std::cout << "EPOLLHUP" << std::endl;
	}
}

void	EpollHandler::disconnectClient(int sd) {
	struct epoll_event	ev;
	int ret = epoll_ctl(epollfd, EPOLL_CTL_DEL, sd, &ev);
}

void	EpollHandler::raiseConnectEvent(int sd) {
	for (int i = 0; i < event_listeners.size(); i++)
		event_listeners[i]->onConnect(sd);
}

void	EpollHandler::raiseDisconnectEvent(int sd) {
	for (int i = 0; i < event_listeners.size(); i++)
		event_listeners[i]->onDisconnect(sd);
}

void	EpollHandler::raiseReceiveEvent(std::string data, int sd) {
	std::cout << "In event listner" << std::endl;
	for (int i = 0; i < event_listeners.size(); i++)
		event_listeners[i]->onReceive(data, sd);
}

void	EpollHandler::addEventListener(IEventListener * listener) {
	event_listeners.push_back(listener);
}

void	EpollHandler::removeEventListener(IEventListener * listener) {
	if (event_listeners.size() == 0)
		return;
	for (std::vector<IEventListener *>::iterator it = event_listeners.begin();
			it != event_listeners.end(); it++) {
		if (*it == listener) {
			event_listeners.erase(it);
			break;
		}
	}
}

void	EpollHandler::clearEventListeners() {
	event_listeners.clear();
}
