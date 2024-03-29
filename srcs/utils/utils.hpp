#ifndef IRC_UTILS_HPP
# define IRC_UTILS_HPP

# include <iostream>
# include <vector>

# include "enable_if.hpp"
# include "u_nullptr.hpp"

template <class T>
std::string		ft_itos(T n, typename ft::enable_if<ft::is_integral<T>::value, bool>::type = true)
{
	char		buffer[2];
	std::string	ret;
	size_t		val;

	buffer[1] = '\0';
	if (n < 0)
	{
		val = n * -1;
		ret + "-";
	}
	else
		val = n;
	while (ret.empty() || val > 0)
	{
		buffer[0] = val % 10 + '0';
		ret.insert(0, buffer);
		val /= 10;
	}
	return (ret);
};
bool			isCharset(char c, std::string charset);

std::vector<std::string>	ft_split(std::string haystack, std::string needle);

std::string	strToUpper(std::string s);
std::string	strToLower(std::string s);
std::string	strReplaceAll(std::string str, std::string const toReplace, std::string const content);

void	IRCsigHandler(int sig);

#endif
