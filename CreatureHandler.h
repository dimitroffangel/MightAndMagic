#ifndef CREATUREHANDLER_H_GUARD
#define CREATUREHANDLER_H_GUARD

#include "Creature.h"

class CreatureHandler
{
private:
	Creature* m_Handler;

public:
	CreatureHandler();
	CreatureHandler(const CreatureHandler&);
	CreatureHandler(const Creature&);
	~CreatureHandler();

	CreatureHandler& operator=(const CreatureHandler&);

	std::string GetTagName() const
	{
		return m_Handler->GetTagName();
	}

	Creature& GetCreature() const
	{
		return *m_Handler;
	}
};

#endif