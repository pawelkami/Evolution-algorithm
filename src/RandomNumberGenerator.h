#ifndef  RANDOMNUMBERGENERATOR_H
#define RANDOMNUMBERGENERATOR_H

#include <math.h>
#include <time.h>
#include <bitset>
#include <random>

class RandomNumberGenerator
{
public:
	~RandomNumberGenerator();
	RandomNumberGenerator(const RandomNumberGenerator& randomNumberGenerator) = delete;
	void operator= (const RandomNumberGenerator& randomNumberGenerator) = delete;
	static RandomNumberGenerator& getInstance();
	void init();
	double getFromUniformDistribution();
	double getFromNormalDistribution();
	double randFrom0To1();
	int randFrom0ToN(int n);
	static unsigned long rand64();
	static unsigned long rand63plus1();
	static unsigned long randBit();
	static unsigned long randBinN(unsigned int n, double p);
	static unsigned long randn(unsigned int n);
	static std::bitset<64> randBitset64();
	static std::bitset<6> randBitset6();
private:
	double a, b, c;
	RandomNumberGenerator();
};

#endif

