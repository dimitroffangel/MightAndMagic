#ifndef DEMON_H_GUARD
#define DEMON_H_GUARD

#include "Creature.h"

class Demon : virtual public Creature
{
private:
	const unsigned startingValuesLevel = 1;
	const float startingValuesExperience = 0;
	const float startingValuesExperienceGives = 200;
	const float startingValuesPowerRating = 4666;
	const float startingValuesHP = 200;
	const float startingValuesMana = 0;
	const float startingValuesAgility = 0;
	const float startingValuesAttack = 47;
	const float startingValuesShots = 0;
	const float startingValuesArmor = 10;
	const float startingValuesStealth = 0;
	const unsigned startingValuesMovementOnBattlefield = 5;

public:
	Demon();
	~Demon();

	virtual void LevelUp() override;
	virtual void Die() override;
	virtual void PassTurn() override; // serves as a defence function
	virtual void Attack(Creature& enemy) override;
	virtual void Defend(Creature& enemy) override;
	virtual void MoveOnBattlefield(const int x, const int y) override;


	virtual GameObject* GetObjectInstance() const;
	virtual Creature* GetCreatureInstance() const;
};

#endif