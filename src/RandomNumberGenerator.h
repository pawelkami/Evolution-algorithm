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
	unsigned long rand64();
	unsigned long rand63plus1();
	unsigned long randBit();
	unsigned long randBinN(unsigned int n, double p);
	unsigned long randn(unsigned int n);
	std::bitset<64> randBitset64();
	std::bitset<6> randBitset6();
	std::bitset<64> allCBitset64();
	std::bitset<64> allDBitset64();
private:
	double a, b, c;
	RandomNumberGenerator();
};

#endif

