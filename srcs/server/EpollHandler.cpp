#include "EpollHandler.hpp"
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdexcept>
#include <cerrno>

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
	struct epoll_event	ev = {};
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
		raiseLoopEndEvent();
	}
}


// function called when epoll signals an event on master_socket / listener

void	EpollHandler::handleListenerActivity() {

	// TODO add epoll event error handler?? Maybe an extra function

	// user ServerSocket wrapper to accept connection
	int	sd = master_socket.accept();

	// add possible events to new client sd
	struct epoll_event	ev = {};
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
		//if file descriptor is invalid
		if (events[index].data.fd < 0)
			throw std::logic_error("Invalid client file descriptor");

		// Read data from socket
		char buffer[512] = {};
		int	received = recv(events[index].data.fd, buffer, sizeof(buffer), 0);

		if (received < 0) {
			if (errno != EAGAIN && errno != EWOULDBLOCK) {
				disconnectClient(events[index].data.fd, "Error receiving data packet");
				throw std::runtime_error("recv() failed");
			}
		}
		else if (received == 0) { // Connection was closed remotey
			disconnectClient(events[index].data.fd, "Connection closed remotely");
		}
		else {
			std::string	data(buffer);
			raiseReceiveEvent(data, events[index].data.fd);
			if (data == "close\r\n" || data == "close") {
				disconnectClient(events[index].data.fd, "DEBUG CLOSE");
				running = 0;
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

void	EpollHandler::disconnectClient(int sd, std::string notification) {
	struct epoll_event	ev = {};
	int ret = epoll_ctl(epollfd, EPOLL_CTL_DEL, sd, &ev);
	if (ret < 0)
		std::cout << "Could not delete client from epoll interest list" << std::endl;
	raiseDisconnectEvent(sd, notification);
}

void	EpollHandler::raiseConnectEvent(int sd) {
	for (std::size_t i = 0; i < event_listeners.size(); i++)
		event_listeners[i]->onConnect(sd);
}

void	EpollHandler::raiseDisconnectEvent(int sd, std::string notification) {
	for (std::size_t i = 0; i < event_listeners.size(); i++)
		event_listeners[i]->onDisconnect(sd, notification);
}

void	EpollHandler::raiseReceiveEvent(std::string data, int sd) {
	for (std::size_t i = 0; i < event_listeners.size(); i++)
		event_listeners[i]->onReceive(data, sd);
}

void	EpollHandler::raiseLoopEndEvent() {
	for (std::size_t i = 0; i < event_listeners.size(); i++)
		event_listeners[i]->onLoopEnd();
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
