#include <cctype>
#include <algorithm>

#include "utils.hpp"

std::string strToUpper(std::string s) {
	std::transform(s.begin(), s.end(), s.begin(),
					[](unsigned char c){ return std::toupper(c); }
					);
	return s;
}

std::string strToLower(std::string s) {
	std::transform(s.begin(), s.end(), s.begin(),
					[](unsigned char c){ return std::tolower(c); }
				  );
	return s;
}
