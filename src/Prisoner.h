#ifndef  PRISONER_H
#define PRISONER_H

#include "RandomNumberGenerator.h"
#include <bitset>
#include <iostream>

#define BATTLES_NMB 64

class Prisoner
{
public:
	Prisoner(std::bitset<6> hist);
	Prisoner();
	~Prisoner();

	std::string toString();
	void resetFitness();
	unsigned getNextDecision();
	void compete(Prisoner& opponent);
	void mutate(double ratio);
	void updateHistory(std::bitset<2> lastBattle);
	void setHistory(std::bitset<6> hist);
	void normalizeFitness(long populationNumber);
	double getNormalizedFitness();
	int getFitness();

	bool getStrategyBit(int idx);
	void setStrategyBit(int idx);
	void resetStrategyBit(int idx);

	bool operator< (const Prisoner& compare) const;
	bool operator> (const Prisoner& compare) const;
private:
	std::bitset<64> strategy;
	std::bitset<6> history;

	int fitness;
	double normalizedFitness;
};

#endif

