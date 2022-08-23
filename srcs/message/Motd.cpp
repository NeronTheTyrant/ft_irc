#include "Motd.hpp"
#include "IRCServer.hpp"
#include "messageBuilder.hpp"
#include <fstream>
#include <string>
#define MOTDFILE "motd"

Motd::Motd() : _nomotd (true) {
	std::fstream	fileStream;
	fileStream.open(MOTDFILE, std::fstream::in);
	if (fileStream.is_open() == false) {
		return ;
	}
	while (fileStream.eof() == false) {
		std::string	line;
		std::getline(fileStream, line);
		while (line.size() > 80) {
			_motd.push_back(line.substr(0, 80));
			line.erase(0, 80);
		}
		_motd.push_back(line);
	}
	if (_motd.size() == 0) {
		return;
	}
	if (_motd[_motd.size() - 1] == "") {
		_motd.pop_back();
	}
	fileStream.close();
	_nomotd = false;
}

std::vector<std::string>	Motd::motd() const {
	return _motd;
}

bool	Motd::nomotd() const {
	return _nomotd;
}

void	Motd::sendMotd(User * target, IRCServer *server) const {
	if (target == u_nullptr || server == u_nullptr) {
		return ;
	}
	if (_nomotd == true) {
		target->send(serverMessageBuilder(*server, commandMessageBuilder(CODE_ERR_NOMOTD, target)));
		return;
	}
	else {
		target->send(serverMessageBuilder(*server, commandMessageBuilder(CODE_RPL_MOTDSTART, target, server->name())));
		for (std::vector<std::string>::const_iterator it = _motd.begin(); it != _motd.end(); ++it) {
			target->send(serverMessageBuilder(*server, commandMessageBuilder(CODE_RPL_MOTD, target, *it)));
		}
		target->send(serverMessageBuilder(*server, commandMessageBuilder(CODE_RPL_ENDOFMOTD, target)));
	}
}
