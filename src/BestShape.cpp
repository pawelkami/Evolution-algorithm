#include "BestShape.h"

BestShape::BestShape(double f, double u)
{
	this->f = f;
	this->u = u;
}

std::pair<double, double> BestShape::EvolutionAlgorithm()
{
	generateFirstPopulation();

	do
	{
		drawTemporaryPopulation();
		reproduceChildren();
		pickBestCharacters();
	} while (stopCondition());
	
	return std::pair<double, double> (A0, A1);
}

void BestShape::generateFirstPopulation()
{

}

void BestShape::drawTemporaryPopulation()
{

}

void BestShape::reproduceChildren()
{

}

void BestShape::pickBestCharacters()
{

}

bool BestShape::stopCondition()
{

}

double BestShape::adaptFunction(double a0, double a1)
{

}