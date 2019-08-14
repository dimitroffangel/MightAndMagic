#ifndef DRAGON_H_GUARD
#define DRAGON_H_GUARD

#include "Creature.h"

class Dragon : virtual public Creature
{
private:
	const char startingValuesSymbol = 'R';
	const unsigned startingValuesLevel = 1;
	const float startingValuesExperience = 0;
	const float startingValuesExperienceGives = 190;
	const float startingValuesPowerRating = 4966;
	const float startingValuesHP = 240;
	const float startingValuesMana = 40;
	const float startingValuesAgility = 9;
	const float startingValuesAttack = 31;
	const float startingValuesShots = 0;
	const float startingValuesArmor = 12;
	const float startingValuesStealth = 0;
	const unsigned startingValuesMovementOnBattlefield = 100;
	
public:
	Dragon();
	~Dragon();

	virtual void LevelUp() override;
	virtual void Die() override;
	virtual void PassTurn() override; // serves as a defence function
	virtual void Attack(Creature&enemy) override;
	virtual void Defend(Creature& enemy) override;
	virtual void MoveOnBattlefield(const int x, const int y) override;


	virtual GameObject* GetObjectInstance() const;
	virtual Creature* GetCreatureInstance() const;
};

#endif