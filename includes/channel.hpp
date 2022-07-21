#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "user.hpp"
# include <list>

class Channel
{
	private:
		std::string		name;
		std::list<User>	user_list;
		std::list<Operator>	user_list;

	public:
		Channel(std::string chan_name, std::string username, std::list<Operator> operators)
		{

		}
};

#endif
