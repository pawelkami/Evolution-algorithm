#include "RandomNumberGenerator.h"



RandomNumberGenerator::RandomNumberGenerator()
{
}


RandomNumberGenerator::~RandomNumberGenerator()
{
}


RandomNumberGenerator& RandomNumberGenerator::getInstance()
{
	static RandomNumberGenerator instance;
	return instance;
}


void RandomNumberGenerator::init()
{
	a = (double)time(nullptr);
	b = (double)time(nullptr);
	c = (double)time(nullptr);
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
		// generuj U o rozkladzie równomiernym U(0,1) 
		double U = getFromUniformDistribution();

		// generuj V o rozkladzie równomiernym
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


double RandomNumberGenerator::randFrom0To1()
{
	static std::random_device rd;
	return (double)rd() / rd.max();
}


int RandomNumberGenerator::randFrom0ToN(int n)
{
	static std::random_device rd;
	return rd() % n;
}


unsigned long RandomNumberGenerator::rand64()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<> dis(0, 63);
	return dis(gen);
}


unsigned long RandomNumberGenerator::rand63plus1()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<> dis(1, 63);
	return dis(gen);
}


unsigned long RandomNumberGenerator::randBit()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<> dis(0, 1);
	return dis(gen);
}


unsigned long RandomNumberGenerator::randBinN(unsigned int n, double p)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::binomial_distribution<> dis(n, p);
	return dis(gen);
}


unsigned long RandomNumberGenerator::randn(unsigned int n)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, n - 1);
	return dis(gen);
}


std::bitset<64> RandomNumberGenerator::randBitset64()
{
	std::bitset<64> bits = 0;
	for (auto i = 0; i < 64; ++i)
	{
		bits[i] = randBit();
	}
	return std::move(bits);
}


std::bitset<6> RandomNumberGenerator::randBitset6()
{
	std::bitset<6> bits = 0;
	for (auto i = 0; i < 6; ++i)
		bits[i] = randBit();
	return std::move(bits);
}


std::bitset<64> RandomNumberGenerator::allCBitset64()
{
	std::bitset<64> bits;
	for (auto i = 0; i < 64; ++i)
	{
		bits.reset(i);
	}
	return bits;
}


std::bitset<64> RandomNumberGenerator::allDBitset64()
{
	std::bitset<64> bits;
	for (auto i = 0; i < 64; ++i)
	{
		bits.set(i);
	}
	return bits;
}