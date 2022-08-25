#include "EpollHandler.hpp"
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdexcept>
#include <cerrno>

EpollHandler::EpollHandler(int16_t port)
	: _epollfd(-1), _masterSocket(port), _interrupt(false) {};

EpollHandler::~EpollHandler() {
	if (_epollfd > 0) {
		struct epoll_event	ev = {};
		epoll_ctl(_epollfd, EPOLL_CTL_DEL, _epollfd, &ev);
		close(_epollfd);
	}
}

void	EpollHandler::setInterruptFlag() {
	_interrupt = true;
}

void	EpollHandler::initMasterSocket() {
	try {
		_masterSocket.init();
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}

void	EpollHandler::reinitMasterSocket() {
	try {
		_masterSocket.reinit();
	} catch (const std::exception & e) {
		std::cout << e.what() << std::endl;
	}
}

void	EpollHandler::restart() {
	reinitMasterSocket();
	struct epoll_event	ev = {};
	epoll_ctl(_epollfd, EPOLL_CTL_DEL, _epollfd, &ev);
	close(_epollfd);
	run();
}

void	EpollHandler::run() {
	// if _masterSocket.is not set
	if (_masterSocket.getsd() == -1)
		throw std::logic_error("EpollHandler: Master socket initialised with invalid socket descriptor");
	// start listening for new connections
	_masterSocket.start();
	// init epoll instance
	_epollfd = epoll_create1(0);
	if (_epollfd < 0)
		throw std::runtime_error("Could not create epoll instance");

	// set master socket.events
	struct epoll_event	ev = {};
	ev.data.fd = _masterSocket.getsd();
	ev.events = EPOLLIN | EPOLLPRI | EPOLLERR | EPOLLHUP;

	// add master socket to epoll interest list
	int ret = epoll_ctl(_epollfd, EPOLL_CTL_ADD, _masterSocket.getsd(), &ev);
	if (ret < 0)
		throw std::runtime_error("Could not add master socket to epoll interest list");

	// event loop
	_running = 1;
	while (_running) {

		// check for new.events
		int nfds = epoll_wait(_epollfd, _events, MAX_EVENTS, 60 * 3 * 1000);
		if (nfds == -1 && _interrupt == false)
			throw std::runtime_error("epoll_wait() failed to wait for.events");

		for (int n = 0; n < nfds; n++) {
			if (_events[n].data.fd == _masterSocket.getsd())
				handleListenerActivity();
			else
				handleClientActivity(n);
		}
		raiseLoopEndEvent();
	}
}

void	EpollHandler::stop() {
	_running = false;
}

// function called when epoll signals an event on _masterSocket./ listener

void	EpollHandler::handleListenerActivity() {

	// TODO add epoll event error handler?? Maybe an extra function

	// user ServerSocket wrapper to accept connection
	int	sd = _masterSocket.accept();

	// add possible.events to new client sd
	struct epoll_event	ev = {};
	ev.data.fd = sd;
	ev.events = EPOLLIN;

	// add new client to epoll interest list
	int ret = epoll_ctl(_epollfd, EPOLL_CTL_ADD, sd, &ev);
	if (ret < 0)
		throw std::runtime_error("Could not add master socket to epoll interest list");

	raiseConnectEvent(sd);
}

// function called when epoll signals an event on client socket

void	EpollHandler::handleClientActivity(int index) {

	if (_events[index].events & EPOLLIN) {
		//if file descriptor is invalid
		if (_events[index].data.fd < 0)
			throw std::logic_error("Invalid client file descriptor");

		// Read data from socket
		char buffer[512] = {};
		int	received = recv(_events[index].data.fd, buffer, sizeof(buffer), 0);

		if (received < 0) {
			if (errno != EAGAIN && errno != EWOULDBLOCK) {
				disconnectClient(_events[index].data.fd, "Error receiving data packet");
				throw std::runtime_error("recv() failed");
			}
		}
		else if (received == 0) { // Connection was closed remotey
			disconnectClient(_events[index].data.fd, "Connection closed remotely");
		}
		else {
			std::string	data(buffer);
			raiseReceiveEvent(data, _events[index].data.fd);
		}
	}
}

void	EpollHandler::disconnectClient(int sd, std::string notification, bool notify) {
	struct epoll_event	ev = {};
	int ret = epoll_ctl(_epollfd, EPOLL_CTL_DEL, sd, &ev);
	if (ret < 0)
		std::cout << "Could not delete client from epoll interest list" << std::endl;
	raiseDisconnectEvent(sd, notification, notify);
}

void	EpollHandler::raiseConnectEvent(int sd) {
	for (std::size_t i = 0; i < _eventListeners.size(); i++)
		_eventListeners[i]->onConnect(sd);
}

void	EpollHandler::raiseDisconnectEvent(int sd, std::string notification, bool notify) {
	for (std::size_t i = 0; i < _eventListeners.size(); i++)
		_eventListeners[i]->onDisconnect(sd, notification, notify);
}

void	EpollHandler::raiseReceiveEvent(std::string data, int sd) {
	for (std::size_t i = 0; i < _eventListeners.size(); i++)
		_eventListeners[i]->onReceive(data, sd);
}

void	EpollHandler::raiseLoopEndEvent() {
	for (std::size_t i = 0; i < _eventListeners.size(); i++)
		_eventListeners[i]->onLoopEnd();
}

void	EpollHandler::addEventListener(IEventListener * listener) {
	_eventListeners.push_back(listener);
}

void	EpollHandler::removeEventListener(IEventListener * listener) {
	if (_eventListeners.size() == 0)
		return;
	for (std::vector<IEventListener *>::iterator it = _eventListeners.begin();
			it != _eventListeners.end(); it++) {
		if (*it == listener) {
			_eventListeners.erase(it);
			break;
		}
	}
}

void	EpollHandler::clearEventListeners() {
	_eventListeners.clear();
}
