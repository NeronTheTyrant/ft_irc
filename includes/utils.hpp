#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include "enable_if.hpp"
# include "u_nullptr.hpp"

template <class T>
std::string		ft_itos(T n, typename ft::enable_if<!std::is_integral<T>::value>::type* = u_nullptr);

#endif
