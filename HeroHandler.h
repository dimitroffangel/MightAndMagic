#ifndef HEROHANDLER_H_GUARD
#define HEROHANDLER_H_GUARD

#include "Hero.h"

class HeroHandler
{
private:
	Hero* m_Handler;

public:
	HeroHandler();
	HeroHandler(const HeroHandler&);
	HeroHandler(const Hero&);
	~HeroHandler();

	HeroHandler& operator=(const HeroHandler&);

	std::string GetTagName() const
	{
		return m_Handler->GetTagName();
	}

	Hero& GetHero() const
	{
		return *m_Handler;
	}
};

#endif