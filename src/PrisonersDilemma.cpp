#include "PrisonersDilemma.h"

PrisonersDilemma::PrisonersDilemma()
	: history(RandomNumberGenerator::getInstance().randBitset6()), parentsNumber(PARNUM), 
	populationNumber(POPNUM), ratioCrossing(RATIOCROSS), ratioMutate(RATIOMUT), competNumber(COMPETNUM), 
	iterationNumber(ITERNUM), actualIteration(0)
{
	initialize();
}

PrisonersDilemma::PrisonersDilemma(std::bitset<6> hist, int popnumb, int parnumb)
	: history(hist), parentsNumber(parnumb), populationNumber(popnumb), 
	ratioCrossing(RATIOCROSS), ratioMutate(RATIOMUT), competNumber(COMPETNUM), 
	iterationNumber(ITERNUM), actualIteration(0)
{
	initialize();
}

PrisonersDilemma::PrisonersDilemma(std::bitset<6> hist, int popnumb, int parnumb, int comnumb)
	: history(hist), parentsNumber(parnumb), populationNumber(popnumb),
	ratioCrossing(RATIOCROSS), ratioMutate(RATIOMUT), competNumber(comnumb), 
	iterationNumber(ITERNUM), actualIteration(0)
{
	initialize();
}

PrisonersDilemma::PrisonersDilemma(std::bitset<6> hist, int popnumb, int parnumb, double rM, double rC) 
	: history(hist), parentsNumber(parnumb), populationNumber(popnumb), 
	ratioCrossing(rC), ratioMutate(rM), competNumber(COMPETNUM), 
	iterationNumber(ITERNUM), actualIteration(0)
{
	initialize();
}

PrisonersDilemma::PrisonersDilemma(std::bitset<6> hist, int popnumb, int parnumb, double rM, double rC, int comnumb)
	: history(hist), parentsNumber(parnumb), populationNumber(popnumb),
	ratioCrossing(rC), ratioMutate(rM), competNumber(comnumb), 
	iterationNumber(ITERNUM), actualIteration(0)
{
	initialize();
}

void PrisonersDilemma::initialize()
{
	for (int i = 0; i < parentsNumber; ++i)
		parents.push_back(Gamer());

	for (int i = 0; i < populationNumber; ++i)
		population.push_back(Gamer());
}

std::string PrisonersDilemma::solve()
{
	Gamer best = geneticAlgorithm();
	std::string result = best.toString();
	
	return result;
}

Gamer PrisonersDilemma::geneticAlgorithm()
{
	std::vector<Gamer> bests;

	compete();
	Gamer best = pickBest();

	while (!stopCondition())
	{
		selection();
		pickToCross();
		crossing();
		mutate();
		compete();

		best = pickBest();
		bests.push_back(best);
	}

	Gamer highest = bests[0];
	for (int i = 1; i < iterationNumber; ++i)
	{
		if (bests[i].betterThan(highest))
			highest = bests[i];
	}
	std::cout << "highest: ";
	highest.displayFitness();
	std::cout << "\nbest(from algorithm): ";
	best.displayFitness();
	return best;
}

bool PrisonersDilemma::stopCondition()
{
	return (actualIteration++ >= iterationNumber);
}

void PrisonersDilemma::selection()
{
	parents.clear();

	for (int i = 0; i < parentsNumber; ++i)
	{
		int bestIter = 0;

		for (int j = 0; j < populationNumber - i; ++j)
		{
			if (population[j].betterThan(population[bestIter]))
				bestIter = j;
		}

		parents.push_back(population[bestIter]);
		population.erase(population.begin() + bestIter);
	}
}

void PrisonersDilemma::pickToCross()
{
	toCross.clear();

	for (int i = 0; i < populationNumber >> 1; ++i)
	{
		bool goToNext = false;

		for (int j = 0; goToNext == false; j = (j + 1) % parentsNumber)
		{
			double draw = RandomNumberGenerator::getInstance().randFrom0To1();

			if (draw < ratioCrossing)
			{
				for (int k = (j + 1) % parentsNumber; ; k = (k + 1) % parentsNumber)
				{
					if (k == j) continue;
					draw = RandomNumberGenerator::getInstance().randFrom0To1();

					if (draw < ratioCrossing)
					{
						toCross.push_back(std::make_pair(parents[j], parents[k]));
						goToNext = true;
						break;
					}
				}
			}
		}
	}

	if (populationNumber % 2 == 1)
	{
		bool goToNext = false;

		for (int j = 0; goToNext == false; j = (j + 1) % parentsNumber)
		{
			double draw = RandomNumberGenerator::getInstance().randFrom0To1();

			if (draw < ratioCrossing)
			{
				for (int k = (j + 1) % parentsNumber; ; k = (k + 1) % parentsNumber)
				{
					if (k == j) continue;
					draw = RandomNumberGenerator::getInstance().randFrom0To1();

					if (draw < ratioCrossing)
					{
						toCross.push_back(std::make_pair(parents[j], parents[k]));
						goToNext = true;
						break;
					}
				}
			}
		}
	}
}

void PrisonersDilemma::crossing()
{
	population.clear();

	for (int i = 0; i < populationNumber; ++i)
		population.push_back(Gamer());

	for (int i = 0; i < populationNumber >> 1; ++i)
	{
		int draw = RandomNumberGenerator::getInstance().randFrom0ToN(64);

		for (int j = 0; j < draw; ++j)
		{
			toCross[i].first.getBit(j) == 0 ? population[i].resetBit(j) : population[i].setBit(j);
			toCross[i].second.getBit(j) == 0 ? population[populationNumber - 1 - i].resetBit(j) : population[populationNumber - 1 - i].setBit(j);
		}
		for (int j = draw; j < 64; ++j)
		{
			toCross[i].second.getBit(j) == 0 ? population[i].resetBit(j) : population[i].setBit(j);
			toCross[i].first.getBit(j) == 0 ? population[populationNumber - 1 - i].resetBit(j) : population[populationNumber - 1 - i].setBit(j);
		}
	}
	toCross.clear();
}

void PrisonersDilemma::mutate()
{
	for (int i = 0; i < populationNumber; ++i)
		population[i].mutate(ratioMutate);
}

void PrisonersDilemma::compete()
{
	unsigned long hist = history.to_ulong();

	for (int i = 0; i < populationNumber; ++i)
	{
		for (int j = i; j < populationNumber; ++j)
			population[i].compete(population[j], hist);
	}
}

Gamer PrisonersDilemma::pickBest()
{
	Gamer best = population[0];

	for (int i = 1; i < populationNumber; ++i)
	{
		if (population[i].betterThan(best))
			best = population[i];
	}

	return best;
}