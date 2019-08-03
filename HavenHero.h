#ifndef HAVENHERO_H_GUARD
#define	HAVENHERO_H_GUARD

#include "Hero.h"

class HavenHero : public Hero
{
private:
	std::string m_Name;

public:
	HavenHero(std::string tag, const unsigned x, const unsigned y, bool isStatic, const char symbol
		, unsigned movesOnTurn, std::string name);
	
	// Creature virtual funcs...
	virtual void LevelUp() override;
	virtual void Die() override;
	virtual void Attack(Creature& enemy) override;
	virtual void Defend(Creature& enemy) override;
	virtual void PassTurn() override;
	virtual void MoveOnBattlefield(const int x, const int y) override;
	virtual GameObject* GetObjectInstance() const override;
	virtual Creature* GetCreatureInstance() const override;

	// Hero virtual funs...
	virtual void MoveOnTurn(int x, int y) override;
	virtual Hero* GetInstance() const override;
};

#endif