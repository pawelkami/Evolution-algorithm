#include "RandomNumberGenerator.h"

RandomNumberGenerator* RandomNumberGenerator::instance = nullptr;

RandomNumberGenerator* RandomNumberGenerator::getInstance() 
{
	if (instance == nullptr) 
	{
		instance = new RandomNumberGenerator();
		instance->init();
	}
	return instance;
}

RandomNumberGenerator::RandomNumberGenerator() { }

void RandomNumberGenerator::init() 
{
	a = time(NULL);
	b = time(NULL);
	c = time(NULL);
}

double RandomNumberGenerator::getFromUniformDistribution() 
{
	static int n;
	static double d, x;

	d = (a + b + c) * 8192;
	x = fmod(d, 4294967291.0);
	a = b; b = c; c = x;

	if (x < (float) 2147483648.0) 
		n = (int)x;
	
	else 
		n = (int)(x - 4294967296.0);

	return (n * 2.3283064365e-10 + 0.5);
}

double RandomNumberGenerator::getFromNormalDistribution() 
{
	bool ok = false;
	double limit = sqrt(2 / 2.718281828);
	double X;

	do 
	{
		// generuj U o rozk³adzie równomiernym U(0,1) 
		double U = getFromUniformDistribution();

		// generuj V o rozk³adzie równomiernym
		// U(-sqrt(2/e),sqrt(2/e))
		double V = 2 * limit * getFromUniformDistribution() - limit;
		X = V / U;

		if (X*X <= 2 * (3 - U*(4 + U))) 
			ok = true;

		else if (X*X <= 2 / U - 2 * U) 
		{
			if (X*X <= -4 * log(U)) 
				ok = true;
		}
	} while (!ok);

	return X;
}