#include "IRCServer.hpp"
#include <map>
#include <vector>

int	main (void) {

	std::map<std::string, std::pair<std::string, std::vector<std::string> > > operatorList;
	operatorList["Agathe"] = std::make_pair("Thepower", std::vector<std::string> (1, "127.0.0.1") );
	IRCServer	server(12345, "chaussette.irc.net", "chaussette", operatorList);
	server.start();
}
