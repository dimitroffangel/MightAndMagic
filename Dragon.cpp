#include "Dragon.h"



Dragon::Dragon() : Creature("Dragon")
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


Dragon::~Dragon()
{
}

void Dragon::LevelUp()
{
	if(m_Level == 2)
	{
		m_Armor = 16;
		m_HP = 260;
	}
}

void Dragon::Die()
{
	// the area around him starts to burn for a few turns...
}

void Dragon::PassTurn()
{
	m_HasPassedTurn = true;
}

void Dragon::Attack(Creature& enemy)
{
	enemy.TakeDamage(m_Attack *m_PowerRating*0.016f + m_Agility*0.07f);
}

void Dragon::Defend(Creature & enemy)
{
}

void Dragon::MoveOnBattlefield(const int x, const int y)
{
	Creature::MoveOnBattlefield(x, y);
	// give surrounding damage to the place where he has traveled
}

GameObject * Dragon::GetObjectInstance() const
{
	return new Dragon(*this);
}

Creature * Dragon::GetCreatureInstance() const
{
	return new Dragon(*this);
}
