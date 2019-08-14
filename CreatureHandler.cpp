#include "CreatureHandler.h"



CreatureHandler::CreatureHandler() : m_Handler(nullptr)
{
}

CreatureHandler::CreatureHandler(const CreatureHandler & other) : m_Handler(nullptr)
{
	if (other.m_Handler)
		m_Handler = other.m_Handler->GetCreatureInstance();
}

CreatureHandler::CreatureHandler(const Creature & creature)
{
	m_Handler = creature.GetCreatureInstance();
}


CreatureHandler::~CreatureHandler()
{
	delete m_Handler;
}

CreatureHandler & CreatureHandler::operator=(const CreatureHandler& rhs)
{
	if (this != &rhs)
	{
		if (m_Handler)
			delete m_Handler;

		if (rhs.m_Handler)
			m_Handler = rhs.m_Handler->GetCreatureInstance();

		else
			m_Handler = nullptr;
	}

	return *this;
}
