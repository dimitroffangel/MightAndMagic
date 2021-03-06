#ifndef CREATURE_H_GUARD
#define CREATURE_H_GUARD

#include "GameObject.h"

#include <vector>

class Creature : public GameObject
{
public:
	static const int PowerRatingThreshold = 200;

protected:
	char m_Symbol;
	unsigned m_Level;
	float m_Experience;
	float m_ExperienceGives;
	float m_PowerRating;
	float m_HP;
	float m_Mana;
	float m_Agility;
	float m_Attack;
	float m_Shots;
	float m_Armor;
	float m_Stealth;
	unsigned m_MovementOnBattlefield;
	bool m_IsRange;
	bool m_IsDead;
	bool m_HasPassedTurn;
	Creature* m_BattleTarget;
	std::vector<COORD> m_TargetRoute;
	// inventory

public:
	Creature();
	Creature(const std::string tag,float level, float experience, float expGives, float powerRating, float hp, float mana, float agility,
		float attack, float shots, float armor, float stealth, float movementOnBattlefield);
	Creature(const std::string tag);
	Creature(const std::string tag, const unsigned x, const unsigned y, bool isStatic, const char symbol);
	virtual ~Creature();

	virtual void LevelUp() = 0;
	virtual void Die() = 0;
	virtual void PassTurn() = 0; // serves as a defence function
	virtual void Attack(Creature& enemy) = 0;
	virtual void Defend(Creature& enemy) = 0;
	void TakeDamage(float damage);
	virtual void MoveOnBattlefield(const int x, const int y) = 0;

	virtual Creature* GetCreatureInstance() const = 0;

	float GetPowerRating() const
	{
		return m_PowerRating;
	}

	float GetHealth() const
	{
		return m_HP;
	}

	int GetMovementLefts() const
	{
		return m_MovementOnBattlefield;
	}

	char GetSymbol() const
	{
		return m_Symbol;
	}

	bool IsRange() const
	{
		return m_IsRange;
	}

	void SetLocation(const int x, const int y)
	{
		m_Position.X = x;
		m_Position.Y = y;
	}

	void SetBattleTarget(Creature& creature)
	{
		m_BattleTarget = &creature;
	}

	const Creature* const GetBattleTarget() const
	{
		return m_BattleTarget;
	}

	void AddLocationToRoad(COORD position)
	{
		m_TargetRoute.push_back(position);
	}

	size_t GetRoadLength() const
	{
		return m_TargetRoute.size();
	}

	COORD GetPositionFromRoute(size_t index) const
	{
		return m_TargetRoute[index];
	}

};

#endif