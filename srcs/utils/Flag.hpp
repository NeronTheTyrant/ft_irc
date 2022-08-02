#ifndef FLAG_HPP
# define FLAG_HPP

class Flag {
private:
	uint32_t	_flags;

public:
	Flag();
	Flag(uint32_t flags);
	~Flag();

	bool	isSet(uint32_t bitMask) const;
	bool	isUnset(uint32_t bitMask) const;

	void	set(uint32_t bitMask);
	void	unset(uint32_t bitMask);
};

#endif
