#include <vector>

class	IEventListener {
public:
	virtual void	onConnect(int sd) = 0;
	virtual void	onDisconnect(int sd) = 0;
	virtual void	onReceive(std::vector<char> data, int sd) = 0;
}
