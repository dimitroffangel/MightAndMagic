#include "Battlefield.h"
#include "Drawing.h"
#include <stdexcept>

void Battlefield::DrawBattlefield()
{
	COORD position;

	for (std::size_t i = 0; i < MAX_HEIGHT; i++)
	{
		position.Y = i;
	
		if (i % MoveableFieldOffset == 0)
		{
			for (std::size_t j = 0; j < MAX_WIDTH; j++)
			{
				position.X = j;

				if (j % CenterRatio == 0 && j > 0)
				{
					DrawingObject::DrawObject(DrawingObject::HConsole, "|", position, 0);
					m_ObjectsDesignOnBattlefield[position.Y][position.X] = '|';
				}
				else
				{
					DrawingObject::DrawObject(DrawingObject::HConsole, "_", position, 0);
					m_ObjectsDesignOnBattlefield[position.Y][position.X] = '_';
				}
			}
		}

		else
		{
			for (std::size_t j = 0; j < MAX_WIDTH; j++)
			{
				position.X = j;

				if (j % CenterRatio == 0 && j > 0)
				{
					position.X -= CenterOFFSetRight;
					DrawingObject::DrawObject(DrawingObject::HConsole, "_", position, 0);
					m_ObjectsDesignOnBattlefield[position.Y][position.X] = '_';

				}
				else
				{
					DrawingObject::DrawObject(DrawingObject::HConsole, " ", position, 0);
					m_ObjectsDesignOnBattlefield[position.Y][position.X] = '_';
				}
			}
		}

	}

	DrawArmy();
}

void Battlefield::ClearBattlefield()
{
	COORD position;

	for (size_t y = 0; y < MAX_HEIGHT; y++)
	{
		position.Y = y;
		for (size_t x = 0; x < MAX_WIDTH; x++)
		{
			position.X = x;
			DrawingObject::DrawObject(DrawingObject::HConsole, " ", position, 0);
		}
	}
}

void Battlefield::SwapCreatures(COORD from, COORD to, bool canActivatePassive)
{
	const unsigned maxStrayFromHero = 6;

	if (!canActivatePassive && 
		(MAX_HEIGHT - to.Y > maxStrayFromHero || MAX_HEIGHT - from.Y > maxStrayFromHero || (from.X == to.X && from.Y == to.Y)))
		return;

	int commanderOnebattalionIndex = GetPosition(m_AttackingCommander, from);
	int commanderTwobattalionIndex = GetPosition(m_DefenderCommander, from);
	int battalionIndex;

	if (commanderOnebattalionIndex != -1) // if there is a marked first unit, change its location...
	{
		battalionIndex = commanderOnebattalionIndex;

		// change the position
		if (!canActivatePassive)
		{
			int commanderOnebattalionIndex_To = GetPosition(m_AttackingCommander, to);

			// change the first marked unit
			m_AttackingCommander->PeekUnit(battalionIndex).SetLocation(to.X, to.Y);
			
			if (commanderOnebattalionIndex_To != -1) // if there is not a unit there			
				m_AttackingCommander->PeekUnit(commanderOnebattalionIndex_To).SetLocation(from.X, from.Y);
		}

		else // there won't be a swap here between batalions but only between a unit and an empty space...
			m_AttackingCommander->PeekUnit(battalionIndex).MoveOnBattlefield(to.X, to.Y);
	}

	else if (commanderTwobattalionIndex != -1) // if the first marked unit is valid and the second one
	{
		battalionIndex = commanderTwobattalionIndex;

		// change the position
		if (!canActivatePassive)
		{
			m_DefenderCommander->PeekUnit(battalionIndex).SetLocation(to.X, to.Y);
			
			int commanderOnebattalionIndex_To = GetPosition(m_DefenderCommander, to);

			m_DefenderCommander->PeekUnit(commanderOnebattalionIndex_To).SetLocation(from.X, from.Y);
		}

		else
			m_DefenderCommander->PeekUnit(battalionIndex).MoveOnBattlefield(to.X, to.Y);
	}

	else
		return;

	// keep the current symbols on that place
	char firstBattalionSymbol[2];
	firstBattalionSymbol[0] = m_ObjectsDesignOnBattlefield[from.Y][from.X];
	firstBattalionSymbol[1] = '\0';

	char secondBattalionSymbol[2];
	secondBattalionSymbol[0] = m_ObjectsDesignOnBattlefield[to.Y][to.X];
	secondBattalionSymbol[1] = '\0';

	// swap the battalion's symbol
	std::swap(m_ObjectsDesignOnBattlefield[from.Y][from.X], m_ObjectsDesignOnBattlefield[to.Y][to.X]);

	// print the result...
	DrawingObject::DrawObject(DrawingObject::HConsole, firstBattalionSymbol, to, 0);
	DrawingObject::DrawObject(DrawingObject::HConsole, secondBattalionSymbol, from, 0);

	// swap the number of warriors in the battalion...
	from.X = from.X - (from.X % CenterRatio);
	from.Y--;

	if (from.X != 0) // cuz the ordering is not symetric and there is a pillar there
		from.X++;

	to.X = to.X - (to.X % CenterRatio);
	to.Y--;

	if (to.X != 0) // cuz the ordering is not symetric and there is a pillar there
		to.X++;

	// I will make the swap manually
	
	char firstBattalionNumber[5];
	char secondBattalionNumber[5];

	firstBattalionNumber[4] = '\0';
	secondBattalionNumber[4] = '\0';

	for (size_t i = 0; i < CenterRatio-1; i++)
	{
		firstBattalionNumber[i] = m_ObjectsDesignOnBattlefield[from.Y][from.X+i];
		secondBattalionNumber[i] = m_ObjectsDesignOnBattlefield[to.Y][to.X + i];

		m_ObjectsDesignOnBattlefield[from.Y][from.X + i] = secondBattalionNumber[i];
		m_ObjectsDesignOnBattlefield[to.Y][to.X + i] = firstBattalionNumber[i];
	}

	// print the changes in the number
	DrawingObject::DrawObject(DrawingObject::HConsole, firstBattalionNumber, to, 0);
	DrawingObject::DrawObject(DrawingObject::HConsole, secondBattalionNumber, from, 0);


}

void Battlefield::MoveCreature(COORD from, COORD to, bool isPlayerOne)
{
	int commanderOneBattalionIndex;
	int commanderTwoBattalionIndex;

	if (isPlayerOne)
	{
		commanderOneBattalionIndex = GetPosition(m_AttackingCommander, from);
		commanderTwoBattalionIndex = GetPosition(m_DefenderCommander, to);
	}

	else
	{
		commanderOneBattalionIndex = GetPosition(m_DefenderCommander, from);
		commanderTwoBattalionIndex = GetPosition(m_AttackingCommander, to);
	}

	int battalionIndex;
	
	// if the first thing to move is empty, no reason to enforce a movement on empty spaces
	if (commanderOneBattalionIndex == -1)
		return;

	if (commanderTwoBattalionIndex == -1) // then a swap will do the job, if validations hold
	{
		if ((isPlayerOne && GetPosition(m_AttackingCommander, to) != -1) || (!isPlayerOne && GetPosition(m_DefenderCommander, to) != -1))
			return;

		battalionIndex = commanderOneBattalionIndex;
		SwapCreatures(from, to, true);
		return;
		// cuz COORD to does not hold a creature from the enemy 
	}
	
	// else there is a fight ahead

	if (isPlayerOne)
		TryMovingCreature(m_AttackingCommander, m_DefenderCommander, commanderOneBattalionIndex, commanderTwoBattalionIndex);
	else
		TryMovingCreature(m_DefenderCommander, m_AttackingCommander, commanderOneBattalionIndex, commanderTwoBattalionIndex);
}

void Battlefield::MakeBotTurn()
{
	/*
		1) iterate through all battalions
		2) find the one minion with lower assessment
		3) set it as a target
		4) if it cannot find, just guard one unit
		5) if the assessment is a lot bigger than the current
	*/

	if (m_NumberOfBots == '1')
	{
		// 1)
		size_t attackerNumberOfBattalions = m_DefenderCommander->GetNumberOfBattalions();
		size_t defenderNumberOfBattalions = m_AttackingCommander->GetNumberOfBattalions();

		Creature* attacker;
		Creature* defender;

		for (size_t i = 0; i < attackerNumberOfBattalions; i++)
		{
			if (m_DefenderCommander->GetNumberOfSoldiersInBattalion(i) == 0)
				continue;

			attacker = &m_DefenderCommander->PeekUnit(i);

			for (size_t j = 0; j < defenderNumberOfBattalions; j++)
			{
				if (m_AttackingCommander->GetNumberOfSoldiersInBattalion(j) == 0)
					continue;

				defender = &m_AttackingCommander->PeekUnit(j);

				//2)
				if (attacker->GetPowerRating() >= defender->GetPowerRating() - Creature::PowerRatingThreshold)
				{
					if (attacker->GetBattleTarget() && attacker->GetBattleTarget()->GetPowerRating() > defender->GetPowerRating())
						continue;

					// 3)
					attacker->SetBattleTarget(*defender);
				}
			}

			// find the best route
			FindBFS(attacker, attacker->GetBattleTarget()->GetPosition(), attacker->GetPosition());

			size_t roadSize = attacker->GetRoadLength();

			// move the attacker now
			if (attacker->GetMovementLefts() >= roadSize)
			{
				COORD moveTo = attacker->GetPositionFromRoute(roadSize - 1);
				MoveCreature(attacker->GetPosition(), moveTo, false);
				MoveCreature(attacker->GetPosition(), attacker->GetBattleTarget()->GetPosition(), false);
			}

			else
			{
				COORD moveTo = attacker->GetPositionFromRoute(attacker->GetMovementLefts());
				MoveCreature(attacker->GetPosition(), moveTo, false);
			}
		}
	}
}

std::string Battlefield::NumberToString(unsigned number) const
{
	// find the length

	unsigned sameNumber = number;
	size_t length = 0;
	int arr[4];
	while (sameNumber != 0)
	{
		// save the digit
		arr[length] = sameNumber % 10;
		sameNumber /= 10; // remove dat digit...
		length++; // increment the lenght of the number
	}

	std::string numberString = "____\0";
	for (size_t i = 0; i < length; i++)
		numberString[length - i - 1] = '0' + arr[i];

	return numberString;
}

void Battlefield::DrawCommanderArmy(Hero* commander, size_t y)
{
	COORD positionCreature;
	positionCreature.Y = y;
	size_t currentBattalionSize;

	for (size_t i = 1; i <= commander->GetNumberOfBattalions(); i++)
	{
		currentBattalionSize = commander->GetNumberOfSoldiersInBattalion(i - 1);

		if (currentBattalionSize == 0) // no need to draw emptiness
			continue;

		// print the creature symbol...
	
		// 1) callibrate the x position
		positionCreature.X = i * 5 - CenterOFFSetRight;

		// 2) get the symbol of the creature
		char battalionSymbol[2];
		battalionSymbol[0] = commander->GetBattalionSymbol(i-1);
		battalionSymbol[1] = '\0';
		
		// 3) move the unit 
		commander->PeekUnit(i-1).SetLocation(positionCreature.X, positionCreature.Y);
		
		// 4) get the amount of dat creature
		std::string numberString = NumberToString(currentBattalionSize);
		
		// 6) draw it finally
		DrawBattalion(positionCreature, battalionSymbol, numberString.c_str());
	}
}

void Battlefield::DrawArmy()
{
	// draw playerOneCommmander's army
	DrawCommanderArmy(m_AttackingCommander, MAX_HEIGHT - 1);

	// do the same for the second commander
	DrawCommanderArmy(m_DefenderCommander, 1);
	

	// draw his army from the bottom
	// do the same for the other commander's army
}

int Battlefield::GetPosition(const Hero* commander, COORD position) const
{
	for (size_t i = 0 ;i  < commander->GetBattalionLength(); i++)
	{
		if (commander->GetNumberOfSoldiersInBattalion(i) == 0)
			continue;
		
		COORD creatureCoord = commander->PeekUnit(i).GetPosition();

		if (creatureCoord.X == position.X && creatureCoord.Y == position.Y)
			return i;
	}

	return -1;
}

void Battlefield::DrawBattalion(COORD positionCreature, const char* battalionSymbol, const char * numberString)
{
	// now this code is a little magical thouu
	// get the position of the number
	COORD positionNumber;
	positionNumber.Y = positionCreature.Y - 1; // the number of soldiers is always on top of the creature
	positionNumber.X = (positionCreature.X + CenterOFFSetRight) / 5; // get the index of the place from left to right
	
	if (positionNumber.X - 1 == 0) // now set the location, but if the index is the 0, then there is a special rule ( =( )
		positionNumber.X = (positionNumber.X - 1) * CenterRatio;
	else
		positionNumber.X = (positionNumber.X - 1) * CenterRatio + 1;

	for (size_t j = 0; j < std::strlen(numberString); j++)
		m_ObjectsDesignOnBattlefield[positionNumber.Y][positionNumber.X + j] = numberString[j];

	m_ObjectsDesignOnBattlefield[positionCreature.Y][positionCreature.X] = battalionSymbol[0];

	DrawingObject::DrawObject(DrawingObject::HConsole, battalionSymbol, positionCreature, 0);
	DrawingObject::DrawObject(DrawingObject::HConsole, numberString, positionNumber, 0);

	for (size_t j = 0; j < std::strlen(numberString); j++)
		m_ObjectsDesignOnBattlefield[positionNumber.Y][positionNumber.X + j] = numberString[j];
}

bool Battlefield::TryKillingBattalion(Creature* &creature, Hero * owner, size_t battalionIndex)
{
	TryEndingBattle();

	if (creature->GetHealth() > 0)
		return false;

	COORD creaturePosition = creature->GetPosition();

	if (owner->GetNumberOfSoldiersInBattalion(battalionIndex) == 1)
	{
		// remove the symbol from the console
		DrawBattalion(creature->GetPosition(), "_", "_____");

		// remove the creature from the container
		owner->RemoveUnit(battalionIndex, 0);	
		
		return true;
	}

	owner->RemoveUnit(battalionIndex, 0);
	creature = &owner->PeekUnit(battalionIndex);
	// set the location of the future first creature in the battalion to the current first
	creature->SetLocation(creaturePosition.X, creaturePosition.Y);

	return false;
}

void Battlefield::TryMovingCreature(Hero* attackerHero, Hero* defenderHero, size_t commanderOneBattalionIndex, size_t commanderTwoBattalionIndex)
{
	Creature* attacker = &attackerHero->PeekUnit(commanderOneBattalionIndex);
	Creature* defender = &defenderHero->PeekUnit(commanderTwoBattalionIndex);
	size_t attackerBattalionLength = attackerHero->GetNumberOfSoldiersInBattalion(commanderOneBattalionIndex);

	// while defender's health is bigger than zero and there are left defenders
	for (size_t i = 0; i < attackerBattalionLength; i++)
	{
		attacker->Attack(*defender);
		defender->Defend(*attacker);

		if (TryKillingBattalion(defender, defenderHero, commanderTwoBattalionIndex))
		{
			if (!TryKillingBattalion(attacker, attackerHero, commanderOneBattalionIndex))
				UpdateBattalionAfterFight(attacker, attackerHero, commanderOneBattalionIndex);

			return;
		}

		if (TryKillingBattalion(attacker, attackerHero, commanderOneBattalionIndex))
		{
			if (!TryKillingBattalion(defender, defenderHero, commanderTwoBattalionIndex))
				UpdateBattalionAfterFight(defender, defenderHero, commanderTwoBattalionIndex);

			return;
		}
	}

	// if no one of the two were killed re-draw the battalion number

	// draw defender...
	char creatureSymbol[2];
	creatureSymbol[0] = defender->GetSymbol();
	creatureSymbol[1] = '\0';
	DrawBattalion(defender->GetPosition(), creatureSymbol,
		NumberToString(defenderHero->GetNumberOfSoldiersInBattalion(commanderTwoBattalionIndex)).c_str());

	creatureSymbol[0] = attacker->GetSymbol();
	DrawBattalion(attacker->GetPosition(), creatureSymbol,
		NumberToString(attackerHero->GetNumberOfSoldiersInBattalion(commanderOneBattalionIndex)).c_str());
}

bool Battlefield::TryMovingOn(COORD fromPosition, COORD targetPosition, COORD& currentDirection, COORD& nearestPosition, 
	float& currentDistance, float& minDistance, int additionX, int additionY) const
{
	if ((fromPosition.X + additionX >= 0 && fromPosition.X + additionX < MAX_WIDTH &&
		fromPosition.Y + additionY >= 0 && fromPosition.Y + additionY < MAX_HEIGHT &&
		!ContainsCreature(fromPosition.X + additionX, fromPosition.Y + additionY)) ||
		(targetPosition.X == fromPosition.X + additionX && targetPosition.Y == fromPosition.Y + additionY))
	{
		currentDirection = fromPosition;
		currentDirection.X += additionX;
		currentDirection.Y += additionY;

		if (targetPosition.X == currentDirection.X && targetPosition.Y == currentDirection.Y)
			return true;

		currentDistance = DistanceBetween(targetPosition, currentDirection);

		if (currentDistance < minDistance)
		{
			nearestPosition = currentDirection;
			minDistance = currentDistance;
		}
	}

	return false;
}

void Battlefield::FindBFS(Creature* warrior, COORD targetPosition, COORD fromPosition)
{
	float currentDistance = 100000001;
	float minDistance = 1000001;
	COORD nearestPosition, currentDirection;

	// top
	if (TryMovingOn(fromPosition, targetPosition, currentDirection, nearestPosition,
		currentDistance, minDistance, 0, static_cast<int>(MoveableFieldOffset) * -1))
		return;
	// top-right
	if (TryMovingOn(fromPosition, targetPosition, currentDirection, nearestPosition,
		currentDistance, minDistance, CenterRatio, static_cast<int>(MoveableFieldOffset) * -1))
		return;
		
	// right
	if (TryMovingOn(fromPosition, targetPosition, currentDirection, nearestPosition, currentDistance, minDistance, CenterRatio, 0))
		return;
	// bot-right
	if (TryMovingOn(fromPosition, targetPosition, currentDirection, nearestPosition,
		currentDistance, minDistance, CenterRatio, MoveableFieldOffset))
		return;
	// bot
	if (TryMovingOn(fromPosition, targetPosition, currentDirection, nearestPosition, currentDistance, minDistance, 0, MoveableFieldOffset))
		return;
	// bot-left
	if (TryMovingOn(fromPosition, targetPosition, currentDirection, nearestPosition,
		currentDistance, minDistance, static_cast<int>(CenterRatio) * -1, MoveableFieldOffset))
		return;
	// left
	if (TryMovingOn(fromPosition, targetPosition, currentDirection, nearestPosition,
		currentDistance, minDistance, static_cast<int>(CenterRatio) * -1, 0))
		return;
	// top-left
	if (TryMovingOn(fromPosition, targetPosition, currentDirection, nearestPosition,
		currentDistance, minDistance, static_cast<int>(CenterRatio) * -1, static_cast<int>(MoveableFieldOffset) * -1))
		return;

	// add the new route
	warrior->AddLocationToRoad(nearestPosition);
	// search the rest of the route
	FindBFS(warrior, targetPosition, nearestPosition);
}

void Battlefield::UpdateBattalionAfterFight(Creature* creature, Hero * owner, size_t battalionIndex)
{
	char creatureSymbol[2];
	creatureSymbol[0] = creature->GetSymbol();
	creatureSymbol[1] = '\0';

	DrawBattalion(creature->GetPosition(), creatureSymbol,
		NumberToString(owner->GetNumberOfSoldiersInBattalion(battalionIndex)).c_str());
}

void Battlefield::TryEndingBattle()
{
	// ::TODO

	if (m_AttackingCommander->GetNumberOfSoldiers() == 0)
	{
		m_IsBattleOver = true;
	}

	else if (m_DefenderCommander->GetNumberOfSoldiers() == 0)
	{
		m_IsBattleOver = true;
	}
}

Hero & Battlefield::FindHero(const std::string tag) const
{
	for (std::vector<HeroHandler>::const_iterator it = m_HeroesOnBattlefield.cbegin(); 
		it != m_HeroesOnBattlefield.end(); it++)
	{
		if (it->GetTagName() == tag)
			return it->GetHero();
	}

	throw std::out_of_range("\n Couldn't find a hero with such a tag... \n");
}

float Battlefield::DistanceBetween(COORD from, COORD to) const
{
	return (from.X - to.X) * (from.X - to.X) + (from.Y - to.Y) * (from.Y - to.Y);
}

bool Battlefield::ContainsCreature(size_t x, size_t y) const
{
	size_t commanderNumberOfBattalions = m_AttackingCommander->GetNumberOfBattalions();
	COORD currentBattalionPosition;

	// check the attacker first for any eventual collision...
	for (size_t i = 0; i < commanderNumberOfBattalions; i++)
	{
		if (m_AttackingCommander->GetNumberOfSoldiersInBattalion(i) == 0)
			continue;

		currentBattalionPosition = m_AttackingCommander->PeekUnit(i).GetPosition();

		if (currentBattalionPosition.X == x && currentBattalionPosition.Y == y)
			return true;
	}

	// switch the number of battalions to the defender
	commanderNumberOfBattalions = m_DefenderCommander->GetNumberOfBattalions();

	// do the same logic for the defender as was as the attacker's examination
	for (size_t i = 0; i < commanderNumberOfBattalions; i++)
	{
		if (m_DefenderCommander->GetNumberOfSoldiersInBattalion(i) == 0)
			continue;
	
		currentBattalionPosition = m_DefenderCommander->PeekUnit(i).GetPosition();

		if (currentBattalionPosition.X == x && currentBattalionPosition.Y == y)
			return true;
	}

	return false;
}

Battlefield::Battlefield(Hero * commanderOne, Hero * commanderTwo)
	:m_AttackingCommander(commanderOne), 
	m_DefenderCommander(commanderTwo),
	m_IsBattleOver(false),
	m_NumberOfBots('\0')
{

	// fill the map with blank spots
	std::string row(MAX_WIDTH, '_');

	m_ObjectsDesignOnBattlefield = vectorString(MAX_HEIGHT, row);
}