#ifndef POPULATION_H
#define POPULATION_H

#include "RandomNumberGenerator.h"
#include "Gamer.h"
#include <iostream>
#include <vector>

class Population
{
public:
	Population(std::bitset<6> history);
private:
	void initialize();
	bool stopCondition();
	void crossing();
	void mutate();
	void compete();

	std::bitset<6> history;		// historia wprowadzana przez uzytkownika
	std::vector<Gamer> population;
	std::vector<Gamer> parents;
	double ratioMutate;
	double ratioCrossing;
};

#endif
