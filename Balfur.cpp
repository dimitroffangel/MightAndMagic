#include "Balfur.h"

#include <time.h>
#include <stdexcept>

int Balfur::GenerateRandomNumber(int n)
{
	if (n <= 0 || n >= RAND_MAX)
		throw std::domain_error("Argument of GenerateRandomNumber() must be between 0 32767... ");

	const int bucket_size = RAND_MAX / n; // divide the random values on intervals so that the random function be more random
	int newRandomNumber;

	do newRandomNumber = rand() / n;
	while (newRandomNumber > n); // else a number will have a bigger chance to be chosen then other

	return newRandomNumber;
}

Balfur::Balfur() :Creature("Balfur")
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
}


Balfur::~Balfur()
{

}

void Balfur::LevelUp()
{
	Dragon::LevelUp();
	Demon::LevelUp();
}

void Balfur::Die()
{
	Dragon::Die();
}

void Balfur::PassTurn()
{
	Dragon::PassTurn();
}

void Balfur::Attack(Creature& enemy)
{
	int randomNumber = GenerateRandomNumber(42);

	if (randomNumber < 21)
		Dragon::Attack(enemy);
	else
		Demon::Attack(enemy);
}

void Balfur::Defend(Creature & enemy)
{
}

void Balfur::MoveOnBattlefield(const int x, const int y)
{
	Dragon::MoveOnBattlefield(x, y);
}

GameObject * Balfur::GetObjectInstance() const
{
	return new Balfur(*this);
}

Creature * Balfur::GetCreatureInstance() const
{
	return new Balfur(*this);
}
