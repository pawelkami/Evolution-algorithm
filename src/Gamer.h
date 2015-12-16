#ifndef GAMER_H
#define GAMER_H

#include "RandomNumberGenerator.h"

class Gamer
{
public:
	Gamer();
	void mutate();
private:
	std::bitset<64> choices;
};

#endif
