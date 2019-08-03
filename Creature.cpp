#include "Creature.h"

void Creature::MoveOnBattlefield(const int x, const int y)
{
	int xDistance = m_Position.X - x;
	int yDistance = m_Position.Y - y;

	if (xDistance < 0)
		xDistance *= -1;
	if (yDistance < 0)
		yDistance *= -1;

	m_MovementOnBattlefield -= xDistance + yDistance;

	if (m_MovementOnBattlefield < 0)
		return;

	m_Position.X = x;
	m_Position.Y = y;
}

Creature::Creature()
{

}

Creature::Creature(const std::string tag, float level, float experience, float expGives, float powerRating, float hp, 
	float mana, float agility, float attack, float shots, float armor, float stealth, float movementOnBattlefield)
{
	m_Tag = tag;
	
	m_IsDead = false;
}

Creature::Creature(const std::string tag)
{
	m_Tag = tag;
}

Creature::Creature(const std::string tag, const unsigned x, const unsigned y, bool isStatic, const char symbol)
	: GameObject(tag, x, y, isStatic, symbol)
{

}

void Creature::TakeDamage(float damage)
{
	m_HP -= damage;
}