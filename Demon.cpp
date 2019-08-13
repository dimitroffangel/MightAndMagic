#include "Demon.h"



Demon::Demon() : Creature("Demon")
{
	m_Level = startingValuesLevel;
	m_Experience = startingValuesExperience;
	m_ExperienceGives = startingValuesExperienceGives;
	m_PowerRating = startingValuesPowerRating;
	m_HP = startingValuesHP;
	m_Mana = startingValuesMana;
	m_Agility = startingValuesAgility;
	m_Attack = startingValuesAttack;
	m_Shots = startingValuesShots;
	m_Armor = startingValuesArmor;
	m_Stealth = startingValuesStealth;
	m_MovementOnBattlefield = startingValuesMovementOnBattlefield;
}


Demon::~Demon()
{
}

void Demon::LevelUp()
{
	if (m_Level == 2)
	{
		m_Attack = 53;
		m_PowerRating = 4800;
		m_Armor++;
	}
}

void Demon::Die()
{
	// it just dies...
}

void Demon::PassTurn()
{
	m_HasPassedTurn = true;
}

void Demon::Attack(Creature& enemy)
{
	enemy.TakeDamage(m_PowerRating * m_Attack * 0.001f);
}

void Demon::Defend(Creature & enemy)
{
}

void Demon::MoveOnBattlefield(const int x, const int y)
{
	Creature::MoveOnBattlefield(x, y);
}

GameObject * Demon::GetObjectInstance() const
{
	return new Demon(*this);
}

Creature * Demon::GetCreatureInstance() const
{
	return new Demon(*this);
}
