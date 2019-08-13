#ifndef BALFUR_H_GUARD
#define BALFUR_H_GUARD 

#include "Demon.h"
#include "Dragon.h"

class Balfur : public Demon, public Dragon
{
private:
	const char startingValuesSymbol = 'B';
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

	int GenerateRandomNumber(int n);

public:
	Balfur();
	~Balfur();

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
