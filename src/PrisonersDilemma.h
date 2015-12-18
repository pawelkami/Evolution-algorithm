#ifndef PRISONERSDILEMMA_H
#define PRISONERSDILEMMA_H

#include "RandomNumberGenerator.h"
#include "Gamer.h"
#include <vector>
#include <algorithm>

#define PARNUM 20
#define POPNUM 30
#define RATIOCROSS 0.8
#define RATIOMUT 0.01
#define ITERNUM 2000

class PrisonersDilemma
{
public:
	PrisonersDilemma();
	PrisonersDilemma(std::string hist, int iternum = ITERNUM);
	PrisonersDilemma(std::bitset<6> hist, int popnumb, int parnumb);
	PrisonersDilemma(std::bitset<6> hist, int popnumb, int parnumb, double rM, double rC);
	std::string solve();
	std::vector<int> getFitnesses();
private:
	void initialize();
	bool stopCondition();
	void pickToCross();
	void crossing();
	void mutate();
	void compete();
	void selection();
	Gamer pickBest();
	Gamer geneticAlgorithm();
	void setHistoryFromString(const std::string& hist);

	int populationNumber;		// liczba potomkow
	int parentsNumber;			// liczba rodzicow
	std::bitset<6> history;		// historia wprowadzana przez uzytkownika
	std::vector<Gamer> population;
	std::vector<Gamer> parents;
	std::vector<std::pair<Gamer, Gamer>> toCross;
	std::vector<int> fitnesses;
	double ratioMutate;
	double ratioCrossing;
	int iterationNumber;		// liczba iteracji w algorytmie
	int actualIteration;		// numer aktualnej iteracji
};

#endif
