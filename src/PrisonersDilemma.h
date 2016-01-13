#ifndef PRISONERSDILEMMA_H
#define PRISONERSDILEMMA_H

#include "Prisoner.h"
#include <string>
#include <bitset>
#include <vector>
#include <algorithm>
#include <iostream>
#include <memory>

class PrisonersDilemma
{
public:
	~PrisonersDilemma();
	PrisonersDilemma(std::string history, int iternum);
	void init(std::string history, int iternum, int popnumber = 20, double rM = 0.001, double rC = 0.8);

	std::string solve();
	std::vector<double> getFitnesses();
private:
	PrisonersDilemma();

	std::bitset<6> history;
	double ratioMutate;
	double ratioCrossing;
	int iterationNumber;
	int currentIteration;
	int populationNumber;

	std::vector<Prisoner> population;
	std::vector<Prisoner> parents;
	std::vector<std::pair<Prisoner, Prisoner> > toCross;
	std::vector<double> populationFitnesses;

	Prisoner geneticAlgorithm();
	bool working();

	void populationCompete();
	void parentsSelection();
	void resetPopulationFitness();
	void pickPairsToCross();
	void parentsCrossing();
	void newGenerationMutate();

	double getPopulationFitness();

	static bool compareFunction(const Prisoner& prisoner1, const Prisoner& prisoner2);
};

#endif


