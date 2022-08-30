#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

namespace ft
{

template <typename>
struct is_integral_base						{ static bool const value = false;};

template <>
struct is_integral_base<bool>				{ static bool const value = true;};

template <>
struct is_integral_base<char>				{ static bool const value = true;};

template <>
struct is_integral_base<unsigned char>		{ static bool const value = true;};
/*
template <>
struct is_integral_base<char16_t>			{ static bool const value = true;};

template <>
struct is_integral_base<char32_t>			{ static bool const value = true;};
*/
template <>
struct is_integral_base<wchar_t>			{ static bool const value = true;};

template <>
struct is_integral_base<short>				{ static bool const value = true;};

template <>
struct is_integral_base<unsigned short>		{ static bool const value = true;};

template <>
struct is_integral_base<int>				{ static bool const value = true;};

template <>
struct is_integral_base<unsigned int>		{ static bool const value = true;};

template <>
struct is_integral_base<long>				{ static bool const value = true;};

template <>
struct is_integral_base<unsigned long>		{ static bool const value = true;};

template <>
struct is_integral_base<long long>			{ static bool const value = true;};

template <>
struct is_integral_base<unsigned long long>	{ static bool const value = true;};

template <class T>
struct is_integral : is_integral_base<T> {};

template<bool Cond, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type; };

}
#endif
