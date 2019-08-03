#ifndef HERO_H_GUARD
#define HERO_H_GUARD

#include <vector>

#include "CreatureHandler.h"
#include "Resource.h"

// abstract class

typedef std::vector< std::vector<CreatureHandler> > Army;

class Hero : public Creature
{
private:
	const size_t BattalionsNumber = 8;
	size_t m_BattalionsLength;
	const float LevelTwoNeededExp = 1000;


protected:
	unsigned m_MovesOnTurn;
	unsigned m_LeftMoves;
	std::vector< std::vector <CreatureHandler> > m_Army;
	std::vector<Resource> m_Resources;

public:
	Hero(const std::string tag, const unsigned x, const unsigned y, bool isStatic, const char symbol, unsigned movesOnTurn);
	virtual ~Hero();

	void ResetMovesOnTurn();
	bool CanMove();
	void TakeResourceField(const Resource& resource);
	virtual void MoveOnTurn(int x, int y) = 0;
	virtual Hero* GetInstance() const = 0;
	void AddArmy(std::vector<CreatureHandler> army);
	void AddUnit(const Creature&, size_t);
	Creature& PeekUnit(size_t battalionIndex) const;
	void RemoveUnit(size_t battalionIndex, size_t index);
	std::string GetArmyInformation() const;
	float GetArmyPowerRating() const;
	size_t GetNumberOfSoldiersInBattalion(size_t indexBattalion) const;
	size_t GetNumberOfSoldiers() const;

	char GetBattalionSymbol(size_t) const;

	unsigned GetLevel() const
	{
		return m_Level;
	}

	const size_t GetBattalionNumber() const
	{
		return BattalionsNumber;
	}

	size_t GetBattalionLength() const
	{
		return m_BattalionsLength;
	}

	void SalvageExp(float exp);
};

#endif