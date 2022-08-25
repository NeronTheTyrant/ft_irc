#ifndef M_O_T_D
# define M_O_T_D
# include <vector>
# include <string>
# include "User.hpp"
# include "IRCServer.hpp"

class Motd {

	public :
		Motd();

		std::vector<std::string>	motd() const;
		bool						nomotd() const;
		void						sendMotd(User * target, IRCServer *server) const;

	private :

		std::vector<std::string>	_motd;
		bool	_nomotd;
};
#endif
