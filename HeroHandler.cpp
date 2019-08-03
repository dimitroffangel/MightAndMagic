#include "HeroHandler.h"



HeroHandler::HeroHandler() : m_Handler(nullptr)
{
}

HeroHandler::HeroHandler(const HeroHandler & other)
{
	if (other.m_Handler)
		m_Handler = other.m_Handler->GetInstance();
}

HeroHandler::HeroHandler(const Hero & hero)
{
	m_Handler = hero.GetInstance();
}

HeroHandler::~HeroHandler()
{
	delete m_Handler;
}

HeroHandler & HeroHandler::operator=(const HeroHandler& rhs)
{
	if (this != &rhs)
	{
		if (m_Handler)
			delete m_Handler;

		if (rhs.m_Handler)
			m_Handler = rhs.m_Handler->GetInstance();

		else
			m_Handler = nullptr;
	}

	return *this;
}
