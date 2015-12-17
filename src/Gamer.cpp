#include "Gamer.h"

Gamer::Gamer()
{
	choices = RandomNumberGenerator::getInstance().randBitset64();
	fitness = 0;
}

void Gamer::mutate(double ratio)
{
	for (int i = 0; i < choices.size(); ++i)
	{
		double draw = RandomNumberGenerator::getInstance().randFrom0To1();
		
		if (draw < ratio)
			choices[i] = !choices[i];
	}
}

std::string Gamer::toString()
{
	return choices.to_string();
}

int Gamer::getBit(int i)
{
	return choices[i];
}

void Gamer::setBit(int i)
{
	choices.set(i);
}

void Gamer::resetBit(int i)
{
	choices.reset(i);
}

/*
	0 - cooperate, 1 - defect

	00 - both players get 3 point
	01 - player 1 gets 0 points, player 2 gets 5 points
	10 - player 1 gets 5 points, player 2 gets 0 points
	11 - both players get 1 point
*/

void Gamer::compete(Gamer opponent, unsigned long hist)
{
	int points;
	
	int code = ((this->choices[hist] << 1) + (opponent.choices[hist]));

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

bool Gamer::betterThan(Gamer compare)
{
	return (this->fitness > compare.fitness);
}

Gamer& Gamer::operator =(const Gamer& g)
{
	this->choices = g.choices;
	this->fitness = g.fitness;
	return *this;
}

// pomocnicza metoda
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
	std::cout << fitness << std::endl;
}