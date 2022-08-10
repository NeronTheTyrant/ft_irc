#include "Client.hpp"

Client::Client(int sd)
	: socket(new DataSocket(sd)) {
	struct sockaddr_in client_addr = {};
// Ask getsockname to fill in this socket's local address
	getsockname(newfd, reinterpret_cast<struct sockaddr*>(&client_addr), &sin_size);
	_hostname = inet_ntoa(client_addr.sin_addr);
}

Client::~Client() {
	delete socket;
}

int	Client::sd() const {
	return socket->getsd();
}

std::string	Client::hostname() const {
	return _hostname;
}

void	Client::setHostname(std::string hostname) {
	_hostname = hostname;
}

void	Client::receive(std::string data) {
	stock += data;
}

void	Client::send(std::string data) const {
	socket->send(data.c_str(), data.size());
}

bool	Client::crlf() const {
	if (stock.find("\r\n") != std::string::npos)
		return true;
	else
		return false;
}

std::string	Client::line() const {
	if (!crlf())
		return std::string("\r\n");
	size_t	pos = stock.find("\r\n");
	return stock.substr(0, pos + 2);
}

void	Client::clearLine() {
	if (!crlf())
		return ;
	size_t	pos = stock.find("\r\n");
	stock.erase(0, pos + 2);
}
