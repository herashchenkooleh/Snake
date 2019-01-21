#pragma once

class Purse
{
public:
	Purse(const unsigned int defaultNumCoins = 150,
			const unsigned int needNumCoins = 1000);

	Purse(Purse&&) = default;
	Purse(const Purse&) = default;

	Purse& operator=(Purse&&) = default;
	Purse& operator=(const Purse&) = default;

	~Purse();

	unsigned int getCoinsCount() const;

	void addCoins(const unsigned int value);
	void removeCoins(const unsigned int value);

	unsigned int getNeedNumCoins() const;

private:
	unsigned int coinsCount;
	unsigned int needNumCoins;
};