#include "Prisoner.h"



Prisoner::Prisoner(std::bitset<6> hist, int flag): strategy(RandomNumberGenerator::getInstance().randBitset64()), history(hist), fitness(0), normalizedFitness(0.0)
{
	if (flag == 1)
		strategy = RandomNumberGenerator::getInstance().allDBitset64();
	if (flag == 0)
		strategy = RandomNumberGenerator::getInstance().allCBitset64();
}


Prisoner::Prisoner() : strategy(RandomNumberGenerator::getInstance().randBitset64()), fitness(0), normalizedFitness(0.0)
{
}


Prisoner::~Prisoner()
{
}


std::string Prisoner::toString()
{
	return strategy.to_string();
}


void Prisoner::resetFitness()
{
	fitness = 0;
	normalizedFitness = 0.0;
}


unsigned Prisoner::getNextDecision()
{
	return (unsigned)strategy[history.to_ulong()];
}


void Prisoner::updateHistory(std::bitset<2> lastBattle)
{
	history >>= 2;
	history[4] = lastBattle[0];
	history[5] = lastBattle[1];
}


void Prisoner::setHistory(std::bitset<6> hist)
{
	history = hist;
}


void Prisoner::compete(Prisoner& opponent)
{
	for (int idx = 0; idx < BATTLES_NMB; ++idx)
	{

		int code = (getNextDecision() << 1) | opponent.getNextDecision();

		std::string historyUpdate;
		std::string opponentHistoryUpdate;

		switch (code)
		{
		case 0:
			this->fitness += 3;
			opponent.fitness += 3;
			historyUpdate = "00";
			opponentHistoryUpdate = "00";
			break;
		case 1:
			opponent.fitness += 5;
			historyUpdate = "01";
			opponentHistoryUpdate = "10";
			break;
		case 2:
			this->fitness += 5;
			historyUpdate = "10";
			opponentHistoryUpdate = "01";
			break;
		case 3:
			this->fitness += 1;
			opponent.fitness += 1;
			historyUpdate = "11";
			opponentHistoryUpdate = "11";
			break;
		default:
			break;
		}

		this->updateHistory(std::bitset<2>(historyUpdate));
		opponent.updateHistory(std::bitset<2>(opponentHistoryUpdate));
	}
}


void Prisoner::normalizeFitness(long totalPoints)
{
	normalizedFitness = ((double)fitness / (double)totalPoints);
}


bool Prisoner::operator< (const Prisoner& compare) const
{
	return (this->normalizedFitness < compare.normalizedFitness);
}


bool Prisoner::operator> (const Prisoner& compare) const
{
	return (this->normalizedFitness > compare.normalizedFitness);
}


double Prisoner::getNormalizedFitness()
{
	return normalizedFitness;
}


int Prisoner::getFitness()
{
	return fitness;
}


bool Prisoner::getStrategyBit(int idx)
{
	return strategy[idx];
}


void Prisoner::setStrategyBit(int idx)
{
	strategy.set(idx);
}


void Prisoner::resetStrategyBit(int idx)
{
	strategy.reset(idx);
}


void Prisoner::mutate(double ratio)
{
	for (int idx = 0; idx < strategy.size(); ++idx)
	{
		double draw = RandomNumberGenerator::getInstance().randFrom0To1();

		if (draw < ratio)
			strategy[idx] = !strategy[idx];
	}
}