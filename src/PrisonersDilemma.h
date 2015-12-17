#ifndef PRISONERSDILEMMA_H
#define PRISONERSDILEMMA_H

#include "RandomNumberGenerator.h"
#include "Gamer.h"
#include <vector>
#include <algorithm>

#define PARNUM 20
#define POPNUM 30
#define RATIOCROSS 0.8
#define RATIOMUT 0.001
#define COMPETNUM 150
#define ITERNUM 200000

class PrisonersDilemma
{
public:
	PrisonersDilemma();
	PrisonersDilemma(std::bitset<6> hist, int popnumb, int parnumb);
	PrisonersDilemma(std::bitset<6> hist, int popnumb, int parnumb, int comnumb);
	PrisonersDilemma(std::bitset<6> hist, int popnumb, int parnumb, double rM, double rC);
	PrisonersDilemma(std::bitset<6> hist, int popnumb, int parnumb, double rM, double rC, int comnumb);
	std::string solve();
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

	int populationNumber;		// liczba potomkow
	int parentsNumber;			// liczba rodzicow
	int competNumber;			// liczba gier pomiedzy dwoma strategrami w fazie 'turnieju'
	std::bitset<6> history;		// historia wprowadzana przez uzytkownika
	std::vector<Gamer> population;
	std::vector<Gamer> parents;
	std::vector<std::pair<Gamer, Gamer>> toCross;
	double ratioMutate;
	double ratioCrossing;
	int iterationNumber;		// liczba iteracji w algorytmie
	int actualIteration;		// numer aktualnej iteracji
};

#endif
