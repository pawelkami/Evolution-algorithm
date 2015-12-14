#ifndef  RANDOMNUMBERGENERATOR_H
#define RANDOMNUMBERGENERATOR_H

#include <math.h>
#include <time.h>

class RandomNumberGenerator 
{
public:
	static RandomNumberGenerator* getInstance();
	void init();
	double getFromUniformDistribution();
	double getFromNormalDistribution();
private:
	double a, b, c;
	static RandomNumberGenerator* instance;
	RandomNumberGenerator();
};

#endif

