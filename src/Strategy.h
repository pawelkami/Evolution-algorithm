#ifndef STRATEGY_H
#define STRATEGY_H

#include "RandomNumberGenerator.h"

class Strategy
{
public:
	Strategy();
private:
	std::bitset<64> choices;
};

#endif
