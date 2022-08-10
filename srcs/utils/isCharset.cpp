#include <iostream>

bool	isCharset(char c, std::string charset)
{
	if (charset.find(c) != std::string::npos)
		return (true);
	return (false);
}
