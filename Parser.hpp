#ifndef PARSER_HPP
# define PARSER_HPP
# include <string>
# include "Command.hpp"

class Parser {

	public :
		Parser( std::string input = std::string() );
		˜Parser();
		std::string	input() const;
		void		setInput( std::string newInput );
		std::string	output() const;
		void		setOutput( std::string newOutput );
		Command &	command() const;

	private :

		std::string input;
		Command		command;
		std::string	output;
};
#endif
