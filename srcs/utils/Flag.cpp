#include "Flag.hpp"

Flag::Flag()
	: _flags(0) {}

Flag::Flag(uint32_t flags)
	: _flags(flags) {}

Flag::~Flag() {}

bool	Flag::isSet(uint32_t bitMask) const {
	if (_flags & bitMask)
		return true;
	else
		return false;
}

bool	Flag::isUnset(uint32_t bitMask) const {
	if (_flags & bitMask)
		return false;
	else
		return true;
}

void	Flag::set(uint32_t bitMask) {
	_flags |= bitMask;
}

void	Flag::unset(uint32_t bitMask) {
	_flags &= ~bitMask;
}
