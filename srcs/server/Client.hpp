#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include "DataSocket.hpp"

class DataSocket;

class	Client {
private:
	DataSocket *	socket;
	std::string		stock;

public:
	Client(int sd);
	~Client();

	int	sd() const;

	void		receive(std::string data);
	void		send(std::string data);
	bool		crlf() const;
	std::string	line();
	void		clearLine();

};

#endif
