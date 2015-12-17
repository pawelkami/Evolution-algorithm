#include "PrisonersDilemma.h"

PrisonersDilemma::PrisonersDilemma()
	: history(RandomNumberGenerator::getInstance().randBitset6()), parentsNumber(PARNUM), 
	populationNumber(POPNUM), ratioCrossing(RATIOCROSS), ratioMutate(RATIOMUT), competNumber(COMPETNUM)
{
	initialize();
}

PrisonersDilemma::PrisonersDilemma(std::bitset<6> hist, int popnumb, int parnumb)
	: history(hist), parentsNumber(parnumb), populationNumber(popnumb), 
	ratioCrossing(RATIOCROSS), ratioMutate(RATIOMUT), competNumber(COMPETNUM)
{
	initialize();
}

PrisonersDilemma::PrisonersDilemma(std::bitset<6> hist, int popnumb, int parnumb, int comnumb)
	: history(hist), parentsNumber(parnumb), populationNumber(popnumb),
	ratioCrossing(RATIOCROSS), ratioMutate(RATIOMUT), competNumber(comnumb)
{
	initialize();
}

PrisonersDilemma::PrisonersDilemma(std::bitset<6> hist, int popnumb, int parnumb, double rM, double rC) 
	: history(hist), parentsNumber(parnumb), populationNumber(popnumb), 
	ratioCrossing(rC), ratioMutate(rM), competNumber(COMPETNUM)
{
	initialize();
}

PrisonersDilemma::PrisonersDilemma(std::bitset<6> hist, int popnumb, int parnumb, double rM, double rC, int comnumb)
	: history(hist), parentsNumber(parnumb), populationNumber(popnumb),
	ratioCrossing(rC), ratioMutate(rM), competNumber(comnumb)
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
	Gamer best;

	//...

	return best;
}

bool PrisonersDilemma::stopCondition()
{
	bool result = false;

	//...

	return result;
}

void PrisonersDilemma::pickToCross()
{
	for (int i = 0; i < populationNumber >> 1; ++i)
	{
		for (int j = 0; j < parentsNumber; j = (j + 1) % parentsNumber)
		{
			int draw = RandomNumberGenerator::getInstance().randFrom0To1();

			if (draw < ratioCrossing)
			{
				for (int k = (j + 1) % parentsNumber; k < parentsNumber; k = (k + 1) % parentsNumber)
				{
					if (k == i) continue;
					draw = RandomNumberGenerator::getInstance().randFrom0To1();

					if (draw < ratioCrossing) 
						toCross.push_back(std::make_pair(parents[j], parents[k]));
				}
			}
		}
	}
}

void PrisonersDilemma::crossing()
{
	pickToCross();

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
	//...
}