#ifndef ARCHER_H_GUARD
#define ARCHER_H_GUARD

#include "Creature.h"

class Archer : public Creature
{
private:
	const char startingValuesSymbol = 'Q';
	const unsigned startingValuesLevel = 1;
	const float startingValuesExperience = 0;
	const float startingValuesExperienceGives = 212;
	const float startingValuesPowerRating = 450;
	const float startingValuesHP = 32;
	const float startingValuesMana = 0;
	const float startingValuesAgility = 9;
	const float startingValuesAttack = 14;
	const float startingValuesShots = 10;
	const float startingValuesArmor = 3;
	const float startingValuesStealth = 1;
	const unsigned startingValuesMovementOnBattlefield = 4;

public:
	Archer();

	virtual void LevelUp() override;
	virtual void Die() override;
	virtual void PassTurn() override; // serves as a defence function
	virtual void Attack(Creature& enemy) override;
	virtual void Defend(Creature& enemy) override;
	virtual void MoveOnBattlefield(const int x, const int y) override;

	virtual GameObject* GetObjectInstance() const override;
	virtual Creature* GetCreatureInstance() const override;
};

#endif