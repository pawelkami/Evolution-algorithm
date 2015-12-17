#include "Gamer.h"

Gamer::Gamer()
{
	choices = RandomNumberGenerator::getInstance().randBitset64();
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

// pomocnicza metoda
void Gamer::display()
{
	for (int i = 0; i < choices.size(); ++i)
	{
		std::cout << choices[i];
	}
}