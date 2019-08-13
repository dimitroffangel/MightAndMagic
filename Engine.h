#ifndef ENGINE_H_GUARD
#define ENGINE_H_GUARD

#include <vector>
#include "Map.h"
#include "Message.h"
#include "Battlefield.h"

typedef std::chrono::time_point<std::chrono::system_clock> CurrentTime;

class Engine
{
private:
	std::vector<Map> m_LoadedMaps;
	Map* m_CurrentMap;
	std::unique_ptr<Battlefield> m_Battle;
	std::vector<Message> m_Messages;
	
	// battle properties
	bool m_IsWaitingConfirmation;
	Hero* m_AboutToAttack;
	Hero* m_AboutToDefend;
	bool isPlayerDead;
	bool isInBattle;
	bool canSwapUnits;
	bool canMoveUnits;
	bool hasMarkedUnit;
	COORD m_HeroPositionBeforeBattle;
	COORD m_MarkedField;

private:
	bool CanMovePlayer(const unsigned xAddtion, const unsigned yAddition);
	void ClearAllMessages();
	void ClearTimesUpMessages();
	void AddMessage(const char* message);
	bool CanPlayerPressKey(CurrentTime& start) const;
	void MovePlayer(const char* playerTag, int moveX, int moveY, const char* leftSymbol, const char* playerSymbol);
	void TryMovingDuringBattle(CurrentTime&);
	void TryMovingDuringNonBattle(CurrentTime&);
	void TryPressingEnter(CurrentTime&);
	void WaitForKeyPress(CurrentTime& start);
	void TryPlayerInteracting();
	void BattleHeroes_QuickSimulation(Hero& attacker, Hero& defender);
	void BattleHeroes_QuickSimulation_RandomCasualties(Hero& attacker, Hero& defender, 
														int randomAttackerTaker, int randomDefenderTaker);
	void AfterBattleLogic();
	void TakeRandomCreatureFromArmy(Hero& heroArmy);
	int GenerateRandomNumber(int n) const;
	void BeforeBattleLogic(Hero&, Hero&);
	void WipeMap();

public:
	Engine(const unsigned, const unsigned);
	Engine(const Map& map);
	~Engine();

	void BeforeStartingGame();
	void OnEachFrame();
	void AddMap(const Map& map);
	bool IsMapLoaded(const char* mapTag) const;
};

#endif