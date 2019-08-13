#ifndef SQUIRE_H_GUARD
#define SQUIRE_H_GUARD

#include "Creature.h"

class Squire : public Creature
{
private:
	//1, 0, 4, 41, 3, 0, 0, 1, 0, 1, 0, 3
	const char startingValuesSymbol = 'S';
	const unsigned startingValuesLevel = 1;
	const float startingValuesExperience = 0;
	const float startingValuesExperienceGives = 4;
	const float startingValuesPowerRating = 41;
	const float startingValuesHP = 3;
	const float startingValuesMana = 0;
	const float startingValuesAgility = 0;
	const float startingValuesAttack = 1;
	const float startingValuesShots = 0;
	const float startingValuesArmor = 1;
	const float startingValuesStealth = 0;
	const unsigned startingValuesMovementOnBattlefield = 10;

public:
	Squire();

	virtual void LevelUp() override;
	
	virtual void Die() override
	{
		// well nothing happens
	}

	virtual void PassTurn() override;
	virtual void Attack(Creature& enemy) override;
	virtual void Defend(Creature& enemy) override;
	virtual void MoveOnBattlefield(const int x, const int y) override;


	virtual GameObject* GetObjectInstance() const;
	virtual Creature* GetCreatureInstance() const;
};


#endif