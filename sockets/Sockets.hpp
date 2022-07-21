#include <cstdint>
#include "EpollHandler.hpp"

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

class Socket {
public:
	Socket();
	virtual ~Socket();

	Socket(Socket & o);
	Socket &	operator=(Socket & o);
	bool		operator==(Socket & o);

	bool	has_error;

protected:
	explicit Socket(int sd);

	int	getsd() const {return sd:;}

	const static int	invalid_socket;
	int			sd;

	friend class EpollHandler;
};

/* Stream Socket class, initialises socket as STEAM_SOCKET using socket() */

class StreamSocket : public Socket {
public:
	StreamSocket();
	explicit StreamSocket(int sd);
};

/* DataSocket, can send and receive data on socket descriptor, assuming there is an active connection */

class DataSocket : public StreamSocket {
public:
	DataSocket();
	explicit DataSocket(int sd);

	void	send (const char * data, std::size_t len);
	void	recv (char * data, std::size_t len);
};

/* Server socket that can accept connections */

class ServerSocket : public StreamSocket {
public:
	ServerSocket(std::uint16_t port);
	
	void	init();
	void	start();
	DataSocker accept();

	uint16_t	port;
};
