#ifndef COMMAND_HPP
# define COMMAND_HPP

# include <string>
# include <vector>

class Command {

	public :

		Command( std::string prefix = std::string (), std::string command = std::string (), std::vector<std::string> arguments = std::vector<std::string> () );
		Command(const Command & src);
		~Command();

		Command &	operator=(const Command & src);

		void		setPrefix( std::string newPrefix );
		std::string	prefix() const;

		void		setCommand( std::string newCommand );
		std::string	command() const;

		void						addArgument( std::string argument );
		std::vector<std::string>	arguments() const;

		void	setSyntaxError(bool status);
		bool	syntaxError() const;

	private :

		std::string					_prefix;
		std::string					_command;
		std::vector<std::string>	_arguments;
		bool						_syntaxError;
};

#endif
