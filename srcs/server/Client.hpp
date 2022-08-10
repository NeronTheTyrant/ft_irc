#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include "DataSocket.hpp"

class DataSocket;

class	Client {
private:
	DataSocket *	socket;
	std::string		stock;
	std::string		_hostname;

public:
	Client(int sd);
	~Client();

	int			sd() const;
	std::string	hostname() const;

	void	setHostname(std::string);

	void		receive(std::string data);
	void		send(std::string data) const;
	bool		crlf() const;
	std::string	line() const;
	void		clearLine();

};

#endif
