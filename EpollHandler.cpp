

EpollHandler::EpollHandler(long int timeout)
	: epollfd(-1), timeout(timeout) {};

EpollHandler::~EpollHandler() {
	if (epollfd > 0)
		close(epollfd);
}

void	EpollHandler::initMasterSocket(int16_t port) {
	try {
		master_socket = ServerSocket(port);
		master_socket.init();
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}

void	EpollHandler::start() {
	if (master_socket->getsd() == -1)
		throw std::logic_error("EpollHandler: Master socket initialised with invalid socket descriptor");

	master_socket.start();

	epollfd = epoll_create1(0);
	if (epollfd < 0)
		throw std::runtime_error("Could not create epoll instance");

	struct epoll_event	ev;
	ev.data.fd = master_socket->getsd();
	ev.events = EPOLLIN | EPOLLPRI | EPOLLERR | EPOLLHUP;

	int ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, master_socket->getsd(), &ev);
	if (ret < 0)
		throw std::runtime_error("Could not add master socket to epoll interest list");

	running = 1;
	while (running) {
		int nfds = epoll_wait(epollfd, events, MAX_EVENTS, timeout);
		if (nfds == -1)
			throw std::runtime_error("epoll_wait() failed to wait for events");

		for (int n = 0; n < nfds; n++) {
			if (events[n].data.fd == master_socket->getsd())
				handleListenerActivity();
			else
				handleClientActivity();
		}
	}
}


void	EpollHandler::handleListenerActivity() {
	DataSocket sd = master_socket.accept();
	
	struct epoll_event	ev;
	ev.data.fd = sd;
	ev.events = EPOLLIN | EPOLLPRI | EPOLLERR | EPOLLHUP;
	
	int ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, sd, &ev);
	if (ret < 0)
		throw std::runtime_error("Could not add master socket to epoll interest list");
}
