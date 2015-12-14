#ifndef BESTSHAPE_H
#define BESTSHAPE_H

#include "RandomNumberGenerator.h"
#include <iostream>
#include <vector>

class BestShape
{
public:
	BestShape(double f, double u);
	std::pair<double, double> EvolutionAlgorithm();
private:
	void generateFirstPopulation();
	void drawTemporaryPopulation();
	void reproduceChildren();
	void pickBestCharacters();
	bool stopCondition();
	double adaptFunction(double a0, double a1);

	double A0, A1;	// optymalizowane zmienne
	double f, u;	// f - wspolczynnik tarcia, u - wspolczynnik lepkosci
	std::vector<double> population;
	std::vector<double> tempPopulation;
	std::vector<double> rePopulation;
};

#endif
