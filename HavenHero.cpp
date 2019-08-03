#include "HavenHero.h"


HavenHero::HavenHero(const std::string tag, const unsigned x, const unsigned y, bool isStatic, const char symbol
	, unsigned movesOnTurn, std::string name) : Hero(tag, x, y, isStatic, symbol, movesOnTurn)
{
	m_Name = name;
}

void HavenHero::LevelUp()
{
}

void HavenHero::Die()
{
}

void HavenHero::Attack(Creature& enemy)
{
}

void HavenHero::Defend(Creature & enemy)
{
}

void HavenHero::PassTurn()
{
}

void HavenHero::MoveOnBattlefield(const int x, const int y)
{
	if (m_LeftMoves == 0)
		return;

	m_Position.X = x;
	m_Position.Y = y;
}

GameObject * HavenHero::GetObjectInstance() const
{
	return new HavenHero(*this);
}

Creature * HavenHero::GetCreatureInstance() const
{
	return new HavenHero(*this);
}

Hero* HavenHero::GetInstance() const
{
	return new HavenHero(*this);
}

void HavenHero::MoveOnTurn(int x, int y) // set Player.X and Player.Y to respectively x and y 
{
	if (m_LeftMoves == 0)
		return;	

	m_LeftMoves--;

	m_Position.X = x;
	m_Position.Y = y;
}
