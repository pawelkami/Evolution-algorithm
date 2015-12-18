#include "Gamer.h"

Gamer::Gamer()
{
	choices = RandomNumberGenerator::getInstance().randBitset64();
	fitness = 0;
	normalizedFitness = 0.0;
}

/*
	Metoda mutuje pojedyncze bity danej strategii z podanym wspolczynnikiem/prawdopodobienstwem
*/
void Gamer::mutate(double ratio)
{
	for (int i = 0; i < choices.size(); ++i)
	{
		double draw = RandomNumberGenerator::getInstance().randFrom0To1();
		
		if (draw < ratio)
			choices[i] = !choices[i];
	}
}

/*
	Metoda zwraca strategie przekonwertowana do string'a
*/
std::string Gamer::toString()
{
	return choices.to_string();
}

/*
	Metoda zwraca wartosc bita o podanym numerze
*/
int Gamer::getBit(int i)
{
	return choices[i];
}

/*
	Metoda ustawia wartosc bita o podanym numerze na 1
*/
void Gamer::setBit(int i)
{
	choices.set(i);
}

/*
	Metoda ustawia wartosc bita o podanym numerze na 0
*/
void Gamer::resetBit(int i)
{
	choices.reset(i);
}

/*
	Metoda porownuje dwie strategie dla danej historii zgodnie z ponizsza tabelka wynikow

	0 - cooperate, 1 - defect

	00 - both players get 3 point
	01 - player 1 gets 0 points, player 2 gets 5 points
	10 - player 1 gets 5 points, player 2 gets 0 points
	11 - both players get 1 point
*/
void Gamer::compete(Gamer& opponent)
{
	for (int i = 0; i < 64; ++i)
	{
		int code = ((this->choices[i] << 1) + (opponent.choices[i]));

		switch (code)
		{
		case 0:
			this->fitness += 3;
			opponent.fitness += 3;
			break;
		case 1:
			opponent.fitness += 5;
			break;
		case 2:
			this->fitness += 5;
			break;
		case 3:
			this->fitness += 1;
			opponent.fitness += 1;
		}
	}
}
/*
	Metoda ma na celu znormalizowanie fitnessa dla pojedynczej strategii
*/
void Gamer::normalizeFitness(int opponentsNumber)
{
	int max = 5 * (opponentsNumber - 1) * 64;
	normalizedFitness = ((double)fitness / (double)max);
}

/*
	Metoda ma na celu wyzerowanie fitnessa i znormalizowanego fitnesa dla pojedynczej strategii
*/
void Gamer::resetFitness()
{
	fitness = 0;
	normalizedFitness = 0.0;
}

/*
	Metoda zwraca wartosc pola normalizedFitness
*/
double Gamer::getNormalFitness()
{
	return normalizedFitness;
}

/*
	Metoda zwraca wartosc pola fitness
*/
int Gamer::getFitness()
{
	return fitness;
}

/*
	Metoda porownuje dwie strategie na podstawie wartosci pol fitness
*/
bool Gamer::betterThan(Gamer& compare)
{
	return (this->fitness > compare.fitness);
}

Gamer& Gamer::operator =(const Gamer& g)
{
	this->choices = g.choices;
	this->fitness = g.fitness;
	this->normalizedFitness = g.normalizedFitness;
	return *this;
}

/*
	Operator porzadku dla funkcji sort
*/
bool Gamer::operator <(const Gamer& compare) const
{
	return(this->normalizedFitness > compare.normalizedFitness);
}

// pomocnicze metody

void Gamer::display()
{
	for (int i = 0; i < choices.size(); ++i)
	{
		std::cout << choices[i];
	}
	std::cout << std::endl;
}

void Gamer::displayFitness()
{
	std::cout << fitness;
}