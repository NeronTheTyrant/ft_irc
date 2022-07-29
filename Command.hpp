#ifndef COMMAND_HPP
# define COMMAND_HPP

class Command {

	public :
		Command( std::string prefix = std::string (), std::string command = std::string (), std::vector<std::string> = std::vector<std::string> () );
		˜Command();
		void setPrefix( std::string newPrefix );
		std::string prefix() const;
		void setCommand( std::string newCommand );
		std::string command() const;
		void	addArgument( std::string argument );
		std::vector<std::string> & arguments();

	private :

		std::string	prefix;
		std::string	command;
		std::vector<std::string>	arguments;
};

#endif
