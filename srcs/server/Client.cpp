#include "Client.hpp"

Client::Client(int sd)
	: socket(new DataSocket(sd)) {}

Client::~Client() {
	delete socket;
}

int	Client::sd() const {
	return socket->getsd();
}

void	Client::receive(std::string data) {
	stock += data;
}

void	Client::send(std::string data) const {
	socket->send(data.c_str(), data.size());
}

bool	Client::crlf() const {
	if (stock.find_first_of("\r\n") != std::string::npos)
		return true;
	else
		return false;
}

/*
 * returns 
 * 	-either an empty string 
 * 	-either an inputted command (amputed from its terminators)
 * 	depending on if the command's input include terminators
 *
*/
std::string	Client::line() const {
	if (!crlf())
		return std::string("");
	size_t	pos = stock.find_first_of("\r\n");
	return stock.substr(0, pos + 1);
}

/*
 * notes 
 * 	clear an inputted command (INCLUDING its terminators)
 * 	does nothing if no terminators were inputted
 *
*/
void	Client::clearLine() {
	if (!crlf())
		return ;
	size_t	pos = stock.find_first_of("\r\n");
	bool	secondTerminator = (pos + 1 < stock.size() && (stock.at(pos + 1) == '\n' || stock.at(pos + 1) == '\r'));
	stock.erase(0, pos + 1 + secondTerminator);
}
