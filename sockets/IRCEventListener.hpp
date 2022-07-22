#include "IEventListener.hpp"
#include <vector>

class IRCEventListeners : public IEventListener {

	void	onConnect(int sd);
	void	onDisconnect(int sd);
	void	onReceive(std::vector<char> data, int sd);
}
