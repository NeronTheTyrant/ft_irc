#include <iostream>
#include <vector>

std::vector<std::string>	ft_split(std::string line, std::string needle) {
	std::vector<std::string>		res;
	std::size_t						i;
	std::size_t						j;

	i = 0;
	while (1) {
		j = i;
		i = line.find(needle, i);
		if (i != j) {
			if (i != std::string::npos)
				res.push_back(line.substr(j, i - j));
			else
				res.push_back(line.substr(j));
		}
		if (i == std::string::npos)
			break ;
		i += needle.length();
	}
	return (res);
}
