#ifndef BATTLEFIELD_H_GUARD
#define BATTLEFIELD_H_GUARD

#include "HeroHandler.h"

typedef std::vector< std::string > vectorString;

class Battlefield
{
private:
	static const unsigned MAX_WIDTH = 45;
	static const unsigned MAX_HEIGHT = 16;
	static const unsigned MoveableFieldOffset = 2;
	static const unsigned CenterRatio = 5;
	static const unsigned CenterOFFSetRight = CenterRatio / 2 +1;

	vectorString m_ObjectsDesignOnBattlefield;
	std::vector<HeroHandler> m_HeroesOnBattlefield;
	Hero* m_Attacker;
	Hero* m_Defender;
	bool m_IsBattleOver;
	char m_NumberOfBots; // 0 -> attacker is bot, 1 -> defender, 2 -> both, -1 -> none

	std::string NumberToString(unsigned number) const;
	void DrawCommanderArmy(Hero* commander, size_t y);
	void DrawArmy();
	int GetPosition(const Hero*, COORD position) const;
	void DrawBattalion(COORD positionCreature, const char* creatureSymbol, const char* stringNumber);
	bool TryKillingBattalion(Creature* &creature, Hero* owner, size_t battalionIndex);
	void TryMovingCreature(Hero* attackerHero, Hero* defenderHero, size_t commanderOneBattalionIndex, size_t commanderTwoBattalionIndex);
	void UpdateBattalionAfterFight(Creature* creature, Hero* owner, size_t battalionIndex);
	void TryEndingBattle();
	Hero& FindHero(const std::string tag);

public:
	Battlefield(Hero* commanderOne, Hero* commanderTwo);
	void DrawBattlefield();
	void ClearBattlefield();
	void SwapCreatures(COORD from, COORD to, bool canActivatePassive);
	void MoveCreature(COORD from, COORD to, bool isPlayerOne);
	void MakeBotTurn();

	unsigned GetWidth() const
	{
		return MAX_WIDTH;
	}

	unsigned GetHeight() const
	{
		return MAX_HEIGHT;
	}

	unsigned GetCenterRatio() const
	{
		return CenterRatio;
	}

	unsigned GetCenterOfsetRight() const
	{
		return CenterOFFSetRight;
	}

	unsigned GetMoveableFieldOffset() const
	{
		return MoveableFieldOffset;
	}

	const Hero* GetAttacker() const
	{
		return m_Attacker;
	}

	const Hero* GetDefender() const
	{
		return m_Defender;
	}

	bool IsBattleOver() const
	{
		return m_IsBattleOver;
	}

	void ForfeitBattle()
	{
		m_IsBattleOver = true;
	}

	void SetNumberOfBots(char number)
	{
		m_NumberOfBots = number;
	}
};

#endif