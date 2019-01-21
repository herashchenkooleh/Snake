#include "Purse.hpp"

Purse::Purse(const unsigned int defaultNumCoins,
				const unsigned int NeedNumCoins)
	: coinsCount(defaultNumCoins)
	, needNumCoins(NeedNumCoins)
{
}

Purse::~Purse()
{
}

unsigned int Purse::getCoinsCount() const
{
	return coinsCount;
}

void Purse::addCoins(const unsigned int value)
{
	coinsCount += value;
}

void Purse::removeCoins(const unsigned int value)
{
	coinsCount -= value;
}

unsigned int Purse::getNeedNumCoins() const
{
	return needNumCoins;
}