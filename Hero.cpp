#include "Hero.h"

#include <map>

Hero::Hero(const std::string tag, const unsigned x, const unsigned y, bool isStatic, const char symbol
	, unsigned movesOnTurn) : Creature(tag, x, y, isStatic, symbol)
{
	m_Army = std::vector<std::vector <CreatureHandler> >(BattalionsSize, std::vector<CreatureHandler>());
	m_LeftMoves = movesOnTurn;
	m_MovesOnTurn = movesOnTurn;
	m_BattalionsLength = 0;
}

Hero::~Hero()
{

}

void Hero::ResetMovesOnTurn()
{
	m_LeftMoves = m_MovesOnTurn;
}

bool Hero::CanMove()
{
	return m_LeftMoves > 0;
}

void Hero::TakeResourceField(const Resource & resource)
{
	m_Resources.push_back(resource);
}

void Hero::AddArmy(std::vector<CreatureHandler> army)
{

}

void Hero::AddUnit(const Creature & unit, size_t battalionIndex)
{
	if (m_Army[battalionIndex].size() == 0)
		m_BattalionsLength++;

	m_Army[battalionIndex].push_back(CreatureHandler(unit));
}

Creature & Hero::PeekUnit(size_t battalionIndex) const
{
	return m_Army[battalionIndex][0].GetCreature();
	// TODO: insert return statement here
}

void Hero::RemoveUnit(size_t battalionIndex, size_t index)
{
	m_Army[battalionIndex].erase(m_Army[battalionIndex].begin() + index);
}

std::string Hero::GetArmyInformation() const
{
	std::map<std::string, unsigned> tableCounts;

	for (Army::const_iterator cit = m_Army.cbegin(); cit != m_Army.cend(); cit++)
	{ 
		for (std::vector<CreatureHandler>::const_iterator citBattalion = cit->cbegin(); citBattalion != cit->end(); citBattalion++)
		{
			if (!tableCounts[citBattalion->GetTagName()])
				tableCounts[citBattalion->GetTagName()] = 1;

			else
				tableCounts[citBattalion->GetTagName()]++;
		}
	}

	std::string result;

	for (auto& record : tableCounts)
	{
		result += " " + record.first + ": " + std::to_string(record.second);
	}

	return result;
}

float Hero::GetArmyPowerRating() const
{
	float result = 0;

	for (Army::const_iterator cit = m_Army.cbegin(); cit != m_Army.cend(); cit++)
		for(std::vector<CreatureHandler>::const_iterator citBattalion = cit->cbegin(); citBattalion != cit->cend(); citBattalion++)
			result += citBattalion->GetCreature().GetPowerRating();

	return result;
}

size_t Hero::GetNumberOfSoldiersInBattalion(size_t indexBattalion) const
{
	return m_Army[indexBattalion].size();
}

size_t Hero::GetNumberOfSoldiers() const
{
	return m_Army.size();
}

char Hero::GetBattalionSymbol(size_t indexBattalion) const
{
	return m_Army[indexBattalion][0].GetCreature().GetSymbol();
}

void Hero::SalvageExp(float exp)
{
	m_Experience += exp;

	if (m_Level == 1 && m_Experience >= LevelTwoNeededExp)
		m_Experience -= LevelTwoNeededExp;
}



