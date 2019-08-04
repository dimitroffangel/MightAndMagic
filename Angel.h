#ifndef ANGEL_H_GUARD
#define ANGEL_H_GUARD

#include "Creature.h"

class Angel : public Creature
{
private:
	const char startingValuesSymbol = 'A';
	const float startingValuesLevel = 1;
	const float startingValuesExperience = 0;
	const float startingValuesExperienceGives = 212;
	const float startingValuesPowerRating = 4866;
	const float startingValuesHP = 180;
	const float startingValuesMana = 0;
	const float startingValuesAgility = 12;
	const float startingValuesAttack = 27;
	const float startingValuesShots = 0;
	const float startingValuesArmor = 9;
	const float startingValuesStealth = 0;
	const float startingValuesMovementOnBattlefield = 100;

public:
	Angel();

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