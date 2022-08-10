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
namespace lol {
	template <class InputIterator, class UnaryPredicate>
	bool	myAllOf<InputIterator, UnaryPredicate>(InputIterator first, InputIterator last, UnaryPredicate pred) {
	
		while (first != last) {
			if (!pred(*first)) {
				return false;
			}
			++first;
		}
		return true;
	}
}
#endif
