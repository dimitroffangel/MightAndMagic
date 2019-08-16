#include "Squire.h"

Squire::Squire() :Creature("Squire")
{
	m_Symbol = startingValuesSymbol;
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

	m_IsRange = false;
}

void Squire::LevelUp()
{
	if (m_Level == 2)
	{
		m_Armor++;
		m_Agility++;
		m_HP++;
	}
}

void Squire::PassTurn()
{
	m_HasPassedTurn = true;
}

void Squire::Attack(Creature& enemy)
{
	enemy.TakeDamage((m_Attack - m_Armor/2) * 1.5f);
	m_MovementOnBattlefield = 0;
}

void Squire::Defend(Creature & enemy)
{
	enemy.TakeDamage((m_Attack / 2) * 1.5f);
}

void Squire::MoveOnBattlefield(const int x, const int y)
{
	Creature::MoveOnBattlefield(x, y);
}

GameObject * Squire::GetObjectInstance() const
{
	return new Squire(*this);
}

Creature * Squire::GetCreatureInstance() const
{
	return new Squire(*this);
}
