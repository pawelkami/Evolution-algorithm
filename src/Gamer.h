#ifndef GAMER_H
#define GAMER_H

#include "RandomNumberGenerator.h"
#include <iostream>

class Gamer
{
public:
	Gamer();
	void mutate(double ratio);
	std::string toString();
	int getBit(int i);
	void setBit(int i);
	void resetBit(int i);
	void display();
private:
	std::bitset<64> choices;
};

#endif
