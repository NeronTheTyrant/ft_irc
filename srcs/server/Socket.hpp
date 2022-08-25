#ifndef SOCKETS_HPP
#define SOCKETS_HPP

#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <stdexcept>
# include <iostream>

//#include "EpollHandler.hpp"
//#include "Client.hpp"
//#include "EpollHandler.hpp"

/* Classes and Features:
 *
 * - Socket : contains a socket descriptor, not initialized by default. Member variable sd is compared to non-member variable invalid_socket to know if sd is invalid
 *
 * - StreamSocket: inherits Socket, and will initialize Socket's sd as a STREAM_SOCKET using a call to socket()
 *
 * - DataSocket : inherits StreamSocket, features wrappers to send() and recv() functions to handle incomplete calls and various errors
 *
 * - ServerSocket: inherits StreamSocket, initialized with a port, features wrapper to accept() call to first assign address to inbound connection, before returning a DataSocket instance	
*/

/* Base socket class, only has a socket descriptor and checks for invalid descriptors */

class EpollHandler;
class Client;

class Socket {
public:
	Socket();
	virtual ~Socket();

	Socket(Socket & o);
	Socket &	operator=(Socket & o);
	bool		operator==(Socket & o);


protected:
	explicit Socket(int sd);

	int	getsd() const {return sd;}

	const static int	invalid_socket;
	int			sd;

	friend class EpollHandler;
	friend class Client;
};



#endif
