#ifndef IRC_UTILS_HPP
# define IRC_UTILS_HPP

# include <iostream>

# include "enable_if.hpp"
# include "u_nullptr.hpp"

template <class T>
std::string		ft_itos(T n, typename ft::enable_if<std::is_integral<T>::value, bool>::type = true)
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
		ret + buffer;
		val /= 10;
	}
	return (ret);
};
bool			isCharset(char c, std::string charset);

#endif
