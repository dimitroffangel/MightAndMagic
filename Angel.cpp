#include "Angel.h"



Angel::Angel() : Creature("Angel")
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

	m_IsDead = false;
}

void Angel::LevelUp()
{
	if (m_Level == 2)
	{
		m_Armor +=2;
		m_Attack *= 4;
	}
}

void Angel::Die()
{
	// nothing for now...
}

void Angel::PassTurn()
{
	bool m_HasPassedTurn = true;
}

void Angel::Attack(Creature& enemy)
{
	float damage = m_Attack * (m_PowerRating / 100);
	enemy.TakeDamage(m_Attack * (m_PowerRating / 100));

	// should check if the enemy is alive;
}

void Angel::Defend(Creature & enemy)
{
	float damage = m_Attack * (m_PowerRating / 100);
	enemy.TakeDamage(m_Attack * (m_PowerRating / 100) / 2);

	// TODO
}

void Angel::MoveOnBattlefield(const int x, const int y)
{

	Creature::MoveOnBattlefield(x, y);
}

GameObject * Angel::GetObjectInstance() const
{
	return new Angel(*this);
}

Creature * Angel::GetCreatureInstance() const
{
	return new Angel(*this);
}
