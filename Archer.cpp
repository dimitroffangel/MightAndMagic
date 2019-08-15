#include "Archer.h"



Archer::Archer() : Creature("Archer")
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

	m_IsRange = true;
	m_IsDead = false;
}

void Archer::LevelUp()
{
	if (m_Level == 2)
	{
		m_Armor += 2;
		m_Attack *= 4;
	}
}

void Archer::Die()
{
	// nothing for now...
}

void Archer::PassTurn()
{
	bool m_HasPassedTurn = true;
}

void Archer::Attack(Creature& enemy)
{
	float damage = m_Attack * (m_PowerRating / 100);
	enemy.TakeDamage(m_Attack * (m_PowerRating / 100));

	// should check if the enemy is alive;
}

void Archer::Defend(Creature& enemy)
{
	float damage = m_Attack * (m_PowerRating / 100);
	enemy.TakeDamage(m_Attack * (m_PowerRating / 100) / 2);

	// TODO
}

void Archer::MoveOnBattlefield(const int x, const int y)
{

	Creature::MoveOnBattlefield(x, y);
}

GameObject* Archer::GetObjectInstance() const
{
	return new Archer(*this);
}

Creature* Archer::GetCreatureInstance() const
{
	return new Archer(*this);
}
