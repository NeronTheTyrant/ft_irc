#ifndef PARSER_HPP
# define PARSER_HPP

# include "Command.hpp"
# include <string>

class Parser {

	public :

		Parser( std::string input = std::string() );
		~Parser();

		std::string	input() const;
		void		setInput( std::string newInput );

		std::string	output() const;
		void		setOutput( std::string newOutput );

		void	parseInput();
		Command	command() const;

	private :

		std::string	_input;
		Command		_command;
		std::string	_output;
};

#endif
