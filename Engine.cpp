#include <chrono>
#include <memory>

#include "Engine.h"
#include "Drawing.h"
#include "HavenHero.h"
#include "Angel.h"
#include "Squire.h"
#include "Balfur.h"
#include "Battlefield.h"
#include <stdexcept>

bool Engine::CanMovePlayer(const unsigned xAddition, const unsigned yAddition)
{
	const Hero& hero = m_CurrentMap->FindHero("Player");
	const COORD heroPosition = hero.GetPosition();

	if (heroPosition.X + xAddition < 0 || heroPosition.X + xAddition >= DrawingObject::WIDTH ||
		heroPosition.Y + yAddition < 0 || heroPosition.Y + yAddition >= DrawingObject::HEIGHT)
		return false;

	return true;
}

void Engine::ClearAllMessages()
{
	for (std::vector<Message>::iterator it = m_Messages.begin(); it != m_Messages.end(); it++)
	{
		size_t sizeString = std::strlen(it->GetAlert());
		std::unique_ptr<char> blankString(new char[std::strlen(it->GetAlert()) + 1]);
		
		for (size_t i = 0; i < sizeString; i++)
			blankString.get()[i] = ' ';
		blankString.get()[sizeString] = '\0';

		DrawingObject::DrawObject(DrawingObject::HConsole, blankString.get(), it->GetPosition(), 0);
		// remove it from the container
		ptrdiff_t diff = it - m_Messages.begin();
		m_Messages.erase(it, it + 1);

		it = m_Messages.begin() + diff;

		if (it == m_Messages.end())
			return;
	}
}

void Engine::ClearTimesUpMessages()
{
	CurrentTime now = std::chrono::system_clock().now();
	std::chrono::duration<float> diff;

	for (std::vector<Message>::iterator it = m_Messages.begin(); it != m_Messages.end(); it++)
	{
		diff = now - it->GetStartingTime();

		if (diff.count() > 5) // delete the message if so
		{
			size_t sizeString = std::strlen(it->GetAlert());
			
			std::unique_ptr<char> blankString(new char[std::strlen(it->GetAlert()) + 1]);

			for (size_t i = 0; i < sizeString; i++)
				blankString.get()[i] = ' ';
			blankString.get()[sizeString] = '\0';

			DrawingObject::DrawObject(DrawingObject::HConsole, blankString.get(), it->GetPosition(), 0);
			// remove it from the container
			ptrdiff_t diff = it - m_Messages.begin();
			m_Messages.erase(it, it + 1);

			it = m_Messages.begin() + diff;

			if (it == m_Messages.end())
				return;
		}
	}
}

void Engine::AddMessage(const char * message)
{
	COORD alertPosition;
	alertPosition.X = 0;
	alertPosition.Y = DrawingObject::HEIGHT - 5;
	DrawingObject::DrawObject(DrawingObject::HConsole, message, alertPosition, 0);
	m_Messages.push_back(Message(message, alertPosition, std::chrono::system_clock().now()));
}

bool Engine::CanPlayerPressKey(CurrentTime& start) const
{
	CurrentTime end = std::chrono::system_clock().now();
	std::chrono::duration<float> diff = end - start;

	if (diff.count() < 0.5f)
		return false;

	start = std::chrono::system_clock().now();

	return true;
}

void Engine::MovePlayer(const char * playerTag, int moveX, int moveY,const char* leftSymbol, const char* playerSymbol)
{
	if (!CanMovePlayer(moveX, moveY))
	{
		const char* message = " You cannot move more for this turn...";
		AddMessage(message);
		
		return;
	}

	Hero& hero = m_CurrentMap->FindHero(playerTag);
	// we do not know how much the map will be and how much iteration the search will take if I put the search before getkeySTate condition

	if (!hero.CanMove())
	{
		const char* message = " You cannot move more for this turn...";
		AddMessage(message);

		return;
	}

	COORD position = hero.GetPosition();
	position.X += moveX;
	position.Y += moveY;

	if (!m_Battle && m_CurrentMap->IsHeroOn(position)) // if it is not in battle check if the player is about to enter a battle...
	{
		Hero& enemyHero = m_CurrentMap->FindHero("EnemyHero");
		const COORD enemyPosition = enemyHero.GetPosition();

		if (enemyPosition.X == position.X && enemyPosition.Y == position.Y)
		{
			BeforeBattleLogic(hero, enemyHero);
			return;
		}
	}

	if(!m_Battle)
		m_CurrentMap->UpdateHero(hero, position, playerSymbol[0]);

	// clear the drawing and add the new one
	DrawingObject::DrawObject(DrawingObject::HConsole, leftSymbol, hero.GetPosition(), 0);
	DrawingObject::DrawObject(DrawingObject::HConsole, playerSymbol, position, 0);

	if (!m_Battle)
		hero.MoveOnTurn(position.X, position.Y);
	else
		hero.MoveOnBattlefield(position.X, position.Y);

	std::string resultMessage = m_CurrentMap->TryPlayerGettingResource("Player");

	if (resultMessage.size() != 0)
	{
		AddMessage(resultMessage.c_str());
		return;
	}
}

void Engine::TryMovingDuringBattle(CurrentTime& start)
{
	if (m_IsWaitingConfirmation || !isInBattle)
		return;

	// move forward
	if ((GetKeyState('W') & 0x8000) && CanPlayerPressKey(start))
		MovePlayer("Player", 0, m_Battle.get()->GetMoveableFieldOffset() * (-1), "|", "<");

	else if ((GetKeyState('D') & 0x8000) && CanPlayerPressKey(start))
		MovePlayer("Player", m_Battle.get()->GetCenterRatio(), 0, "|", "<");

	else if ((GetKeyState('S') & 0x8000) && CanPlayerPressKey(start))
		MovePlayer("Player", 0, m_Battle.get()->GetMoveableFieldOffset(), "|", "<");

	else if ((GetKeyState('A') & 0x8000) && CanPlayerPressKey(start))
		MovePlayer("Player", m_Battle.get()->GetCenterRatio() * (-1), 0, "|", "<");
}

void Engine::TryMovingDuringNonBattle(CurrentTime& start)
{
	if (m_IsWaitingConfirmation || isInBattle)
		return;

	// move forward
	if ((GetKeyState('W') & 0x8000) && CanPlayerPressKey(start))
		MovePlayer("Player", 0, -1, "_", "^");

	else if ((GetKeyState('D') & 0x8000) && CanPlayerPressKey(start))
		MovePlayer("Player", 1, 0, "_", ">");

	else if ((GetKeyState('S') & 0x8000) && CanPlayerPressKey(start))
		MovePlayer("Player", 0, 1, "_", "v");

	else if ((GetKeyState('A') & 0x8000) && CanPlayerPressKey(start))
		MovePlayer("Player", -1, 0, "_", "<");
}

void Engine::TryPressingEnter(CurrentTime& start)
{
	if (!(GetKeyState(VK_RETURN) & 0x8000) || !isInBattle || !CanPlayerPressKey(start))
		return;

	const Hero& hero = m_CurrentMap->FindHero("Player");
	COORD heroPosition = hero.GetPosition();

	if (!hasMarkedUnit)  // mark the current unit
	{
		m_MarkedField = heroPosition;
		m_MarkedField.Y += 1;
		m_MarkedField.X -= m_Battle.get()->GetCenterOfsetRight();
		hasMarkedUnit = true;

		return;
	}

	//else
	COORD newMarkedField = heroPosition;
	newMarkedField.X -= m_Battle.get()->GetCenterOfsetRight();
	newMarkedField.Y += 1;

	if (canSwapUnits)
		m_Battle.get()->SwapCreatures(m_MarkedField, newMarkedField, false);
	if (canMoveUnits)
		m_Battle.get()->MoveCreature(m_MarkedField, newMarkedField, true);
	
	if (m_Battle->IsBattleOver())
		AfterBattleLogic();

	hasMarkedUnit = false;
}

void Engine::WaitForKeyPress(CurrentTime& start)
{
	if (m_IsWaitingConfirmation && (GetKeyState('U') & 0x8000))
	{
		// simulate the battle
		BattleHeroes_QuickSimulation(*m_AboutToAttack, *m_AboutToDefend);
		m_IsWaitingConfirmation = false;

		if (m_AboutToDefend->GetNumberOfSoldiers() == 0)
		{
			m_AboutToAttack->SalvageExp(m_AboutToDefend->GetLevel() * 1.f);
			m_CurrentMap->RemoveHero(m_AboutToDefend->GetTagName());
			// get exp from the enemy
		}
		else if (m_AboutToAttack->GetNumberOfSoldiers() == 0)
		{
			m_CurrentMap->RemoveHero(m_AboutToAttack->GetTagName());
			isPlayerDead = true;
		}

		// do not point to them, because the info is not needed any more

		m_AboutToAttack = nullptr;
		m_AboutToDefend = nullptr;
		return;
	}

	if (m_IsWaitingConfirmation && (GetKeyState('Y') & 0x8000))
	{
		m_IsWaitingConfirmation = false;
		isInBattle = true;
		canSwapUnits = true;
		WipeMap();
		
		m_Battle.release();

		std::unique_ptr<Battlefield> ptr_Battlefield(new Battlefield(m_AboutToAttack, m_AboutToDefend));
		
		m_Battle = std::move(ptr_Battlefield);
		m_Battle->DrawBattlefield();

		unsigned battleWidth = m_Battle.get()->GetWidth();
		unsigned battleHeight = m_Battle.get()->GetHeight();
		unsigned battleGetRatio = m_Battle.get()->GetCenterRatio();
		unsigned moveableFieldOffeset = m_Battle.get()->GetMoveableFieldOffset();
		
		Hero& hero = m_CurrentMap->FindHero("Player");
		COORD position = hero.GetPosition();
		m_HeroPositionBeforeBattle = position;

		position.Y = battleHeight - moveableFieldOffeset;
		position.X = battleGetRatio;

		DrawingObject::DrawObject(DrawingObject::HConsole, "<", position, 0);

		// move the object
		hero.MoveOnTurn(position.X, position.Y);

		ClearAllMessages();
		// add a new Message
		const char* message = " You can swap positions of your battalions, when yer' ready press Y";
		AddMessage(message);

		/* 
			1) instantiate a new battlefield, there everything will be drawn
			2) set isInBattle to true

		*/
	}

	TryMovingDuringNonBattle(start);
	TryMovingDuringNonBattle(start);
	TryMovingDuringBattle(start);
	TryPressingEnter(start);

	if ((GetKeyState('T') & 0x8000) && !m_IsWaitingConfirmation)
	{
		if (isInBattle && canSwapUnits)
		{
			canSwapUnits = false;
			canMoveUnits = true;
			return;
		}


		// finish turn
		m_CurrentMap->UpdateChanges();
	}

	if ((GetKeyState('R') & 0x8000) && isInBattle)
		AfterBattleLogic();

	return;
}

void Engine::TryPlayerInteracting()
{
	Hero& hero = m_CurrentMap->FindHero("Player");
}

void Engine::BattleHeroes_QuickSimulation(Hero& attacker, Hero& defender)
{
	float attackerArmyRating = attacker.GetArmyPowerRating();
	float defenderArmyRating = defender.GetArmyPowerRating();

	float battleCoefficient = attackerArmyRating / defenderArmyRating;

	// the casualties are randomised for the time being
	if (battleCoefficient <= 0.5f) // decisive defeat for the attacker // demolish the attacker
	{
		int randomDefenderTaker = GenerateRandomNumber(1) + 1;
		
		BattleHeroes_QuickSimulation_RandomCasualties(attacker, defender, 10, randomDefenderTaker);
	}

	else if (battleCoefficient < 0.75f) // major defeat
	{
		int randomAttackerTaker = GenerateRandomNumber(1) + 3;
		int randomDefenderTaker = std::abs(1 - randomAttackerTaker);

		BattleHeroes_QuickSimulation_RandomCasualties(attacker, defender, randomAttackerTaker, randomDefenderTaker);
	}

	else if (battleCoefficient < 0.9f) // minor defeat
	{
		int randomAttackerTaker = GenerateRandomNumber(1) + 6;
		int randomDefenderTaker = GenerateRandomNumber(1) + 7;

		BattleHeroes_QuickSimulation_RandomCasualties(attacker, defender, randomAttackerTaker, randomDefenderTaker);
	}

	else if (battleCoefficient < 1.2f) // stalemate
	{
		int randomAttackerTaker = GenerateRandomNumber(5) + 2;
		int randomDefenderTaker = GenerateRandomNumber(5) + 2;

		BattleHeroes_QuickSimulation_RandomCasualties(attacker, defender, randomAttackerTaker, randomDefenderTaker);
	}

	else if (battleCoefficient >= 1.2f && battleCoefficient < 1.4f) // minor victory
	{
		int randomAttackerTaker = GenerateRandomNumber(1) + 7;
		int randomDefenderTaker = GenerateRandomNumber(1) + 5;

		BattleHeroes_QuickSimulation_RandomCasualties(attacker, defender, randomAttackerTaker, randomDefenderTaker);
	}

	else if (battleCoefficient >= 1.4f && battleCoefficient < 1.6f) // major victory
	{
		int randomDefenderTaker = GenerateRandomNumber(1) + 3;
		int randomAttackerTaker = std::abs(1 - randomDefenderTaker);

		BattleHeroes_QuickSimulation_RandomCasualties(attacker, defender, randomAttackerTaker, randomDefenderTaker);
	}

	else if (battleCoefficient >= 1.6f && battleCoefficient <= 1.8f) // decisive victory
	{
		int randomDefenderTaker = GenerateRandomNumber(1) + 1;
		int randomAttackerTaker = std::abs(1 - randomDefenderTaker);

		BattleHeroes_QuickSimulation_RandomCasualties(attacker, defender, randomAttackerTaker, randomDefenderTaker);
	}

	else // demolish the defender
	{
		int randomAttackerTaker = GenerateRandomNumber(1)+1;

		BattleHeroes_QuickSimulation_RandomCasualties(attacker, defender, randomAttackerTaker, 10);
	}
}

void Engine::BattleHeroes_QuickSimulation_RandomCasualties(Hero & attacker, Hero & defender, 
	int randomAttackerTaker, int randomDefenderTaker)
{
	unsigned attackerCasualties = static_cast<unsigned>(attacker.GetNumberOfSoldiers() * (randomAttackerTaker / 10.0f));
	unsigned defenderCasualties = static_cast<unsigned>(defender.GetNumberOfSoldiers() * (randomDefenderTaker/ 10.0f));

	while (attackerCasualties > 0)
	{
		TakeRandomCreatureFromArmy(attacker);
		attackerCasualties--;
	}

	// now take soldiers from the defender
	while (defenderCasualties > 0)
	{
		TakeRandomCreatureFromArmy(defender);
		defenderCasualties--;
	}
}

void Engine::AfterBattleLogic()
{
	m_Battle->ForfeitBattle();

	const Hero* attacker = m_Battle->GetAttacker();

	if (attacker->GetNumberOfSoldiers() == 0)
	{
		DrawingObject::DrawObject(DrawingObject::HConsole, " ", attacker->GetPosition(), 0);
		m_CurrentMap->UpdateHero(*attacker, attacker->GetPosition(), '_');
		m_CurrentMap->RemoveHero(attacker->GetTagName());
	}

	const Hero* defender = m_Battle->GetDefender();

	if (defender->GetNumberOfSoldiers() == 0)
	{
		DrawingObject::DrawObject(DrawingObject::HConsole, " ", defender->GetPosition(), 0);
		m_CurrentMap->UpdateHero(*defender, defender->GetPosition(), '_');
		m_CurrentMap->RemoveHero(defender->GetTagName());
	}

	// now redraw the map
	isInBattle = false;
	//WipeMap();

	//m_Battle->DrawBattlefield();
	m_Battle->ClearBattlefield();
	m_Battle.reset();

	Hero& hero = m_CurrentMap->FindHero("Player");
	COORD position = hero.GetPosition();

	hero.SetLocation(m_HeroPositionBeforeBattle.X, m_HeroPositionBeforeBattle.Y);

	DrawingObject::DrawObject(DrawingObject::HConsole, "<", position, 0);

	// draw objects
	DrawingObject::DrawMap(*m_CurrentMap);

	ClearAllMessages();

	/*
		1) instantiate a new battlefield, there everything will be drawn
		2) set isInBattle to true
	*/
}

void Engine::TakeRandomCreatureFromArmy(Hero & heroArmy)
{
	// TODO

	unsigned armySize = heroArmy.GetNumberOfSoldiers();

	size_t soldierIndexToDie = GenerateRandomNumber(armySize);

	size_t battalionIndex = -1;

	while (battalionIndex < 0 || battalionIndex >= heroArmy.GetNumberOfBattalions())
		battalionIndex = GenerateRandomNumber(8);

	heroArmy.RemoveUnit(soldierIndexToDie, battalionIndex);
}

int Engine::GenerateRandomNumber(int n) const
{
	if (n <= 0 || n >= RAND_MAX)
		throw std::domain_error("Argument of GenerateRandomNumber() must be between 0 32767... ");

	const int bucket_size = RAND_MAX / n; // divide the random values on intervals so that the random function be more random
	int newRandomNumber;

	do newRandomNumber = rand() / n;
	while (newRandomNumber >= n); // else a number will have a bigger chance to be chosen then other

	return newRandomNumber;
}

void Engine::BeforeBattleLogic(Hero& hero, Hero& enemyHero)
{
	m_AboutToAttack = &hero;
	m_AboutToDefend = &enemyHero;

	m_IsWaitingConfirmation = true;

	std::string message = "You are approaching a foe, you can run and face some loss or fight, the army consists of: "
		+ enemyHero.GetArmyInformation() + "Press Y to fight or for quick simulation U, or N to retreat...";

	AddMessage(message.c_str());
}

void Engine::WipeMap()
{
	DrawingObject::WipeMeshes(*m_CurrentMap);
}

Engine::Engine(unsigned width, unsigned height)
	:canMoveUnits(false), canSwapUnits(false), hasMarkedUnit(false),
	isInBattle(false), isPlayerDead(false), m_AboutToAttack(nullptr), m_AboutToDefend(nullptr), m_HeroPositionBeforeBattle(),
	m_IsWaitingConfirmation(false), m_MarkedField()
{
	m_CurrentMap = new Map(width, height);
	m_LoadedMaps.push_back(*m_CurrentMap);

}

Engine::Engine(const Map & map)
	:canMoveUnits(false), canSwapUnits(false), hasMarkedUnit(false),
	isInBattle(false), isPlayerDead(false), m_AboutToAttack(nullptr), m_AboutToDefend(nullptr), m_HeroPositionBeforeBattle(),
	m_IsWaitingConfirmation(false), m_MarkedField()
{
	m_CurrentMap = new Map(map);
	m_LoadedMaps.push_back(*m_CurrentMap);
}

Engine::~Engine()
{
	delete m_CurrentMap;
}

void Engine::BeforeStartingGame()
{
	// set srand
	std::srand(static_cast<unsigned>(time(NULL)));

	//// set the console writing mechaninishm
	DrawingObject::HConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(DrawingObject::HConsole);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(DrawingObject::HConsole, &csbi);
	DrawingObject::WIDTH = csbi.srWindow.Right - csbi.srWindow.Left+1;
	DrawingObject::HEIGHT = csbi.srWindow.Bottom - csbi.srWindow.Top+1;

	// add the objects and the map
	HavenHero player("Player", 0, 0, false, '>', 3, "Lysander");

	// just a test...
	for (size_t i = 0; i < 3; i++)
		player.AddUnit(Angel(), 0);


	for (size_t i = 0; i < 123; i++)
		player.AddUnit(Squire(), 1);

	for (size_t i = 0; i < 5; i++)
		player.AddUnit(Squire(), 2);

	Resource resourceMinerals("Resource-Minerals", 2, 2, true, '*', "Minerals", 100);
	Resource resourceWoods("Resource-Woods", 4, 4, true, 'W', "Woods", 120);

	HavenHero enemy("EnemyHero", 1, 0, true, 'E', 5, "Arthas");

	// just a test...
	for (size_t i = 0; i < 2; i++)
		enemy.AddUnit(Angel(), 0);
/*
	for (size_t i = 0; i < 0; i++)
		enemy.AddUnit(Squire(), 1);*/

	m_CurrentMap->AddHero(player);
	m_CurrentMap->AddResource(resourceMinerals);
	m_CurrentMap->AddResource(resourceWoods);
	m_CurrentMap->AddHero(enemy);

	// draw objects
	DrawingObject::DrawMap(*m_CurrentMap);
}

void Engine::OnEachFrame()
{
	CurrentTime start = std::chrono::system_clock().now();

	while (true)
	{
		WaitForKeyPress(start);
		ClearTimesUpMessages();
	}
}

void Engine::AddMap(const Map & map)
{
	m_LoadedMaps.push_back(map);
}
