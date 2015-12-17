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
	void displayFitness();
	void compete(Gamer opponent);
	void normalizeFitness(int opponentsNumber);
	double getNormalFitness();
	bool betterThan(Gamer compare);
	Gamer& operator =(const Gamer& g);
	bool operator <(const Gamer& compare) const;
private:
	std::bitset<64> choices;
	int fitness;
	double normalizedFitness;
};

#endif
