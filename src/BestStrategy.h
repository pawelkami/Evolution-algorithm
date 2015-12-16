#ifndef BESTSTRATEGY_H
#define BESTSTRATEGY_H

#include "RandomNumberGenerator.h"
#include "Strategy.h"
#include <iostream>
#include <vector>

class BestStrategy
{
public:
	BestStrategy(std::bitset<6> history);
	Strategy geneticAlgorithm();
private:
	void initialize();
	bool stopCondition();
	void crossing();
	void mutate();
	void compete();


	std::bitset<6> history;		// historia wprowadzana przez uzytkownika
	std::vector<Strategy> population;
	std::vector<Strategy> parents;
	double ratioMutate;
	double ratioCrossing;
};

#endif
