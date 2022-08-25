#include <iostream>

bool	ft_isdigit(std::string s) {
	for (std::string::iterator it = s.begin(); it != s.end(); ++it) {
		if (!std::isdigit(*it))
			return (false);
	}
	return (true);
}
