#include "PrisonersDilemma.h"
#include <assert.h>

PrisonersDilemma::PrisonersDilemma()
	: history(RandomNumberGenerator::getInstance().randBitset6()), parentsNumber(PARNUM), 
	populationNumber(POPNUM), ratioCrossing(RATIOCROSS), ratioMutate(RATIOMUT), 
	iterationNumber(ITERNUM), actualIteration(0)
{
	initialize();
}

PrisonersDilemma::PrisonersDilemma(std::string hist, int iternum) 
	: parentsNumber(PARNUM), populationNumber(POPNUM), ratioCrossing(RATIOCROSS), ratioMutate(RATIOMUT),
	iterationNumber(iternum), actualIteration(0)
{
	setHistoryFromString(hist);
	initialize();
}

PrisonersDilemma::PrisonersDilemma(std::bitset<6> hist, int popnumb, int parnumb)
	: history(hist), parentsNumber(parnumb), populationNumber(popnumb), 
	ratioCrossing(RATIOCROSS), ratioMutate(RATIOMUT), iterationNumber(ITERNUM), actualIteration(0)
{
	initialize();
}

PrisonersDilemma::PrisonersDilemma(std::bitset<6> hist, int popnumb, int parnumb, double rM, double rC) 
	: history(hist), parentsNumber(parnumb), populationNumber(popnumb), 
	ratioCrossing(rC), ratioMutate(rM), iterationNumber(ITERNUM), actualIteration(0)
{
	initialize();
}

/*
	Metoda inicjuje vectory rodzicow i populacji
*/
void PrisonersDilemma::initialize()
{
	for (int i = 0; i < parentsNumber; ++i)
		parents.push_back(Gamer());

	for (int i = 0; i < populationNumber; ++i)
		population.push_back(Gamer());
}

/*
	Jedyna metoda publiczna, ktora wywoluje algorytm genetyczny i zwraca najlepsza strategie w postaci string'a
*/
std::string PrisonersDilemma::solve()
{
	Gamer best = geneticAlgorithm();
	std::string result = best.toString();
	
	return result;
}

/*
	Metoda symulujaca wlasciwy algorytm genetyczny, rozwiazujacy dylemat wieznia
*/
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
		makeNewPopulation();
		//---------------------
		best = pickBest();
		bests.push_back(best);
		fitnesses.push_back(best.getFitness());
	}

	Gamer highest = bests[0];
	for (int i = 1; i < iterationNumber; ++i)
	{
		if (bests[i].betterThan(highest))
			highest = bests[i];
	}
	std::cout << "highest: ";
	highest.displayFitness();
	std::cout << std::endl;
	std::cout << "best(from algorithm): ";
	best.displayFitness();
	std::cout << std::endl;
	std::cout << std::endl;

	best.compete(highest);
	best.normalizeFitness(2);
	highest.normalizeFitness(2);
	std::cout << "Highest normalizedFitness: ";
	std::cout << highest.getNormalFitness() << std::endl;
	std::cout << "best(from algorithm): ";
	std::cout << best.getNormalFitness() << std::endl;

	return best;
}

void PrisonersDilemma::setHistoryFromString(const std::string & hist)
{
	assert(hist.size() == 6);
	for (unsigned int i = 0; i < hist.size(); ++i)
	{
		if (hist[i] == '1')
			history.set(i);
		else if (hist[i] == '0')
			history.reset(i);
	}
}

/*
	Metoda odpowiedzialna za konczenie dzialania algorytmu
	Jest w najprostszej postaci, czyli konczy algorytm po zadanej liczbie iteracji
*/
bool PrisonersDilemma::stopCondition()
{
	return (actualIteration++ >= iterationNumber);
}

/*
	Metoda odpowiedzialna za selekcje osobnikow z populacji do vectora rodzicow
	metoda kola ruletki
*/
void PrisonersDilemma::selection()
{
	parents.clear();

	std::sort(population.begin(), population.end());

	for (int i = 0; i < parentsNumber; ++i)
	{
		double draw = RandomNumberGenerator::getInstance().randFrom0To1();
		double sumNormFitn = 0.0;

		for (int j = 0; j < populationNumber; ++j)
		{
			sumNormFitn += population[j].getNormalFitness();

			if (sumNormFitn >= draw)
			{
				parents.push_back(population[j]);
				break;
			}
		}
	}

	std::cout << std::endl << "--------------------------------SELECTION--------------------------------" << std::endl;
	for (int i = 0; i < population.size(); ++i)
	{
		population[i].displayFitness();
		std::cout << " ";
	}
	std::cout << std::endl << std::endl;
	for (int i = 0; i < parents.size(); ++i)
	{
		parents[i].displayFitness();
		std::cout << " ";
	}
	std::cout << std::endl << "-------------------------------------------------------------------------" << std::endl;
}

/*
	Metoda paruje rodzicow i zapisuje pary w pomocniczym vektorze
	liczba par jest polowa liczby potomkow, bo z kazdej pary bedzie
	powstawac para potomkow w wyniku krzyzowania pary rodzicow
*/
void PrisonersDilemma::pickToCross()
{
	std::cout << "-------------------------------PICK TO CROSS----------------------------" << std::endl;
	toCross.clear();

	std::sort(parents.begin(), parents.end());

	for (int i = 0; i < populationNumber >> 1; ++i)
	{
		bool goToNext = false;

		for (int j = 0; goToNext == false; j = (j + 1) % parentsNumber)
		{
			double draw = RandomNumberGenerator::getInstance().randFrom0To1();

			if (draw < ratioCrossing)
			{
				for (int k = 0; ; k = (k + 1) % parentsNumber)
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
				for (int k = 0; ; k = (k + 1) % parentsNumber)
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

	for (int i = 0; i < parents.size(); ++i)
	{
		parents[i].displayFitness();
		std::cout << " ";
	}
	std::cout << std::endl << std::endl;

	for (int i = 0; i < toCross.size(); ++i)
	{
		toCross[i].first.displayFitness();
		std::cout << " ";
		toCross[i].second.displayFitness();
		std::cout << " | ";
	}
	std::cout << std::endl;
	std::cout << "-------------------------------------------------------------------------" << std::endl;
}

/*
	Metoda odpowiedzialna za krzyzowanie par rodzicow wczesniej wybranych i
	zapisanych w pomocniczym vektorze toCross, w ten sposob zostaje 
	wygenerowana nowa populacja
*/
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

	if (populationNumber % 2 == 1)
	{
		int i = (populationNumber >> 1) + 1;
		int draw = RandomNumberGenerator::getInstance().randFrom0ToN(64);

		for (int j = 0; j < draw; ++j)
			toCross[i].first.getBit(j) == 0 ? population[i].resetBit(j) : population[i].setBit(j);
		for (int j = draw; j < 64; ++j)
			toCross[i].second.getBit(j) == 0 ? population[i].resetBit(j) : population[i].setBit(j);
	}

	std::cout << "--------------------------------CROSSING--------------------------------" << std::endl;
	for (int i = 0; i < toCross.size(); ++(++i))
	{
		toCross[i >> 1].first.display();
		toCross[i >> 1].second.display();
		std::cout << std::endl;
		population[i].display();
		population[i + 1].display();
		std::cout << "---------------------------------------" << std::endl;
	}
	std::cout << "------------------------------------------------------------------------" << std::endl;

	toCross.clear();
}

/*
	Metoda, ktorej celem jest mutacja kazdego osobnika z populacji
	(realizacja przez wywolanie metody klasy Gamer dla kazdego osobnika)
*/
void PrisonersDilemma::mutate()
{
	for (int i = 0; i < populationNumber; ++i)
		population[i].mutate(ratioMutate);
}

/*
	Metoda, ktora kazde dwa osobniki z populacji ze soba porownuje i wylicza dla nich fitness
	(realizacja przez wywolanie metody klasy Gamer dla kazdego osobnika)
*/
void PrisonersDilemma::compete()
{
	for (int i = 0; i < populationNumber; ++i)
	{
		for (int j = i+1; j < populationNumber; ++j)
			population[i].compete(population[j]);
	}

	for (int i = 0; i < populationNumber; ++i)
		population[i].normalizeFitness(populationNumber);
}

/*
	Metoda wybiera najlepszego osobnika z populacji
*/
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

/*
	Metoda zwraca tablice wartosci funkcji przystosowania najlepszych osobnikow z kazdej iteracji
*/
std::vector<int> PrisonersDilemma::getFitnesses()
{
	return fitnesses;
}

/*
Metoda z nowo powstalej wstepnej populacji tuz po mutowaniu oraz z rodzicow tworzy nowa populacje najlepszych
*/
void PrisonersDilemma::makeNewPopulation()
{
	std::cout << "--------------------------------MAKE NEW POPULATION--------------------------------" << std::endl;
	for (int i = 0; i < population.size(); ++i)
	{
		population[i].displayFitness();
		std::cout << " ";
	}
	std::cout << std::endl << std::endl;

	for (int i = 0; i < parents.size(); ++i)
	{
		parents[i].displayFitness();
		std::cout << " ";
	}
	std::cout << std::endl << std::endl;

	std::vector<Gamer> temp;

	temp.insert(temp.begin(), population.begin(), population.end());
	temp.insert(temp.end(), parents.begin(), parents.end());

	for (int i = 0; i < temp.size(); ++i)
	{
		temp[i].displayFitness();
		std::cout << " ";
	}
	std::cout << std::endl << std::endl;

	std::sort(temp.begin(), temp.end());

	for (int i = 0; i < temp.size(); ++i)
	{
		temp[i].displayFitness();
		std::cout << " ";
	}
	std::cout << std::endl << std::endl;

	population.clear();

	population.insert(population.begin(), temp.begin(), temp.begin() + populationNumber);

	for (int i = 0; i < population.size(); ++i)
	{
		population[i].displayFitness();
		std::cout << " ";
	}
	std::cout << std::endl << std::endl;
	std::cout << "-----------------------------------------------------------------------------------" << std::endl;
}