#include "PrisonersDilemma.h"



PrisonersDilemma::PrisonersDilemma()
{
}


PrisonersDilemma::~PrisonersDilemma()
{
}

PrisonersDilemma::PrisonersDilemma(std::string history, int iternum)
{
	init(history, iternum);
}


bool PrisonersDilemma::compareFunction(const Prisoner& prisoner1, const Prisoner& prisoner2)
{
	return prisoner1 > prisoner2;
}


void PrisonersDilemma::init(std::string hist, int iternum, int popnumber, double rM, double rC)
{
	history = std::bitset<6>(hist);
	iterationNumber = iternum;
	currentIteration = 0;
	populationNumber = popnumber;
	ratioMutate = rM;
	ratioCrossing = rC;

	population.clear();
	parents.clear();
	toCross.clear();

	for (unsigned idx = 0; idx < populationNumber; ++idx)
		population.push_back(Prisoner(history));
}


void PrisonersDilemma::resetPopulationFitness()
{
	for (int idx = 0; idx < populationNumber; ++idx)
		population[idx].resetFitness();
}


bool PrisonersDilemma::working()
{
	return (currentIteration++ < iterationNumber);
}


void PrisonersDilemma::populationCompete()
{
	resetPopulationFitness();

	for (int i_idx = 0; i_idx < populationNumber; ++i_idx)
	{
		for (int j_idx = i_idx + 1; j_idx < populationNumber; ++j_idx)
		{
			population[i_idx].compete(population[j_idx]);

			population[i_idx].setHistory(history);
			population[j_idx].setHistory(history);
		}
	}

	long totalScore = 0;
	for (int idx = 0; idx < populationNumber; ++idx)
		totalScore += population[idx].getFitness();

	for (int idx = 0; idx < populationNumber; ++idx)
		population[idx].normalizeFitness(totalScore);
}


/*
Metoda odpowiedzialna za selekcje osobnikow z populacji do vectora rodzicow
metoda kola ruletki
*/
void PrisonersDilemma::parentsSelection()
{
	parents.clear();

	std::sort(population.begin(), population.end(), compareFunction);

	for (int i_idx = 0; i_idx < populationNumber; ++i_idx)
	{
		double draw = RandomNumberGenerator::getInstance().randFrom0To1();
		double sumNormFitn = 0.0;

		for (int j_idx = 0; j_idx < populationNumber; ++j_idx)
		{
			sumNormFitn += population[j_idx].getNormalizedFitness();

			if (sumNormFitn >= draw)
			{
				parents.push_back(population[j_idx]);
				break;
			}
		}
	}
}


/*
Metoda paruje rodzicow i zapisuje pary w pomocniczym vektorze
liczba par jest polowa liczby potomkow, bo z kazdej pary bedzie
powstawac para potomkow w wyniku krzyzowania pary rodzicow
*/
void PrisonersDilemma::pickPairsToCross()
{
	toCross.clear();

	std::sort(parents.begin(), parents.end(), compareFunction);

	for (int i_idx = 0; i_idx < ((populationNumber >> 1) + (populationNumber % 2)); ++i_idx)
	{
		bool goToNext = false;

		for (int j_idx = 0; goToNext == false; j_idx = (j_idx + 1) % populationNumber)
		{
			double draw = RandomNumberGenerator::getInstance().randFrom0To1();

			if (draw < ratioCrossing)
			{
				for (int k_idx = 0; ; k_idx = (k_idx + 1) % populationNumber)
				{
					if (k_idx == j_idx) continue;
					draw = RandomNumberGenerator::getInstance().randFrom0To1();

					if (draw < ratioCrossing)
					{
						toCross.push_back(std::make_pair(parents[j_idx], parents[k_idx]));
						goToNext = true;
						break;
					}
				}
			}
		}
	}
}


/*
Metoda odpowiedzialna za krzyzowanie par rodzicow wczesniej wybranych i
zapisanych w pomocniczym vektorze toCross, w ten sposob zostaje
wygenerowana nowa populacja
*/
void PrisonersDilemma::parentsCrossing()
{
	for (int i = 0; i < populationNumber >> 1; ++i)
	{
		int draw = RandomNumberGenerator::getInstance().randFrom0ToN(64);

		for (int j = 0; j < draw; ++j)
		{
			toCross[i].first.getStrategyBit(j) == 0 ? population[i].resetStrategyBit(j) : population[i].setStrategyBit(j);
			toCross[i].second.getStrategyBit(j) == 0 ? population[populationNumber - 1 - i].resetStrategyBit(j) : population[populationNumber - 1 - i].setStrategyBit(j);
		}
		for (int j = draw; j < 64; ++j)
		{
			toCross[i].second.getStrategyBit(j) == 0 ? population[i].resetStrategyBit(j) : population[i].setStrategyBit(j);
			toCross[i].first.getStrategyBit(j) == 0 ? population[populationNumber - 1 - i].resetStrategyBit(j) : population[populationNumber - 1 - i].setStrategyBit(j);
		}
	}

	if (populationNumber % 2 == 1)
	{
		int i = (populationNumber >> 1);
		int draw = RandomNumberGenerator::getInstance().randFrom0ToN(64);

		for (int j = 0; j < draw; ++j)
			toCross[i].first.getStrategyBit(j) == 0 ? population[i].resetStrategyBit(j) : population[i].setStrategyBit(j);
		for (int j = draw; j < 64; ++j)
			toCross[i].second.getStrategyBit(j) == 0 ? population[i].resetStrategyBit(j) : population[i].setStrategyBit(j);
	}

	toCross.clear();
}


double PrisonersDilemma::getPopulationFitness()
{
	long max = 3 * BATTLES_NMB * (populationNumber - 1) * populationNumber;

	long sum = 0;
	for (int idx = 0; idx < populationNumber; ++idx)
		sum += population[idx].getFitness();

	double popFitness = (double)sum / (double)max;
	return popFitness;
}


void PrisonersDilemma::newGenerationMutate()
{
	for (int i = 0; i < populationNumber; ++i)
		population[i].mutate(ratioMutate);
}


Prisoner PrisonersDilemma::geneticAlgorithm()
{
	int _populationNumber;
	std::vector<Prisoner> _population;

	_populationNumber = populationNumber;
	_population = population;

	for (int i = 0; i < _populationNumber; ++i)
	{
		population.push_back(Prisoner(history, 0));
	}
	populationNumber *= 2;
	populationCompete();
	double befAllCFitness = getPopulationFitness();
	coeff.push_back(befAllCFitness);

	population = _population;
	populationNumber = _populationNumber;

	for (int i = 0; i < _populationNumber; ++i)
	{
		population.push_back(Prisoner(history, 1));
	}
	populationNumber *= 2;
	populationCompete();
	double befAllDFitness = getPopulationFitness();
	coeff.push_back(befAllDFitness);

	population = _population;
	populationNumber = _populationNumber;

	int idx = 0;
	double sum = 0;
	while (working())
	{
		populationCompete();
		sum += getPopulationFitness();
		++idx;
		if (idx == (iterationNumber/100))
		{
			double avgFitness = sum / (iterationNumber/100);
			populationFitnesses.push_back(avgFitness);
			idx = 0;
			sum = 0;
		}
		parentsSelection();
		pickPairsToCross();
		parentsCrossing();
		newGenerationMutate();
	}

	_populationNumber = populationNumber;
	_population = population;

	for (int i = 0; i < _populationNumber; ++i)
	{
		population.push_back(Prisoner(history, 0));
	}
	populationNumber *= 2;
	populationCompete();
	double aftAllCFitness = getPopulationFitness();
	coeff.push_back(aftAllCFitness);

	population = _population;
	populationNumber = _populationNumber;

	for (int i = 0; i < _populationNumber; ++i)
	{
		population.push_back(Prisoner(history, 1));
	}
	populationNumber *= 2;
	populationCompete();
	double aftAllDFitness = getPopulationFitness();
	coeff.push_back(aftAllDFitness);

	population = _population;
	populationNumber = _populationNumber;

	std::sort(population.begin(), population.end(), compareFunction);

	return population[0];
}


std::string PrisonersDilemma::solve()
{
	Prisoner winner = geneticAlgorithm();
	return winner.toString();
}

std::vector<double> PrisonersDilemma::getFitnesses()
{
	return populationFitnesses;
}


std::vector<double> PrisonersDilemma::getCoeffs()
{
	return coeff;
}

