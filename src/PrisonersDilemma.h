#ifndef PRISONERSDILEMMA_H
#define PRISONERSDILEMMA_H

#include "RandomNumberGenerator.h"
#include "Gamer.h"
#include <vector>

#define PARNUM 20
#define POPNUM 10
#define RATIOCROSS 0.2
#define RATIOMUT 0.2
#define COMPETNUM 150

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
};

#endif
