#include "Gamer.h"
#include "PrisonersDilemma.h"
#include "RandomNumberGenerator.h"

int main()
{
	PrisonersDilemma pris;

	std::string best = pris.solve();
	std::cout << best << std::endl;

	getchar();

	return 0;
}