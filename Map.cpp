#include "Map.h"

#include <iterator>

Map::Map() : m_MapWidth(0), m_MapHeight(0)
{

}

Map::Map(const unsigned mapWidth, const unsigned mapHeight) : m_MapWidth(mapWidth), m_MapHeight(mapHeight)
{
	// set the map...
	
	// fill the map with blank spots
	std::string row(mapWidth, '_');

	m_ObjectsDesignOnMap = vectorString(mapHeight, row);
}

void Map::UpdateChanges()
{
	// give turn to the bots TODO

	// give turn to the player once more
	FindHero("Player").ResetMovesOnTurn();
}

void Map::AddResource(const Resource & resource)
{
	m_ObjectsDesignOnMap[resource.GetPosition().X][resource.GetPosition().Y] = resource.GetObjectSymbol();

	m_ResourcesOnMap.push_back(resource);
}

void Map::AddHero(const Hero & hero)
{
	m_ObjectsDesignOnMap[hero.GetPosition().Y][hero.GetPosition().X] = hero.GetObjectSymbol();

	m_HeroesOnMap.push_back(HeroHandler(hero));
}

void Map::RemoveHero(const std::string tag)
{
	for (std::vector<HeroHandler>::iterator it = m_HeroesOnMap.begin(); it != m_HeroesOnMap.end(); it++)
	{
		// search for the tag
		if (it->GetTagName() == tag)
		{
			// remove the object
			m_HeroesOnMap.erase(it, it + 1);
			return;
		}
	}
}

Hero& Map::FindHero(const std::string tag)
{
	// TODO: insert return statement here

	for (std::vector<HeroHandler>::iterator it = m_HeroesOnMap.begin(); it != m_HeroesOnMap.end(); it++)
	{
		if (it->GetTagName() == tag)
			return it->GetHero();
	}
}

std::string Map::TryPlayerGettingResource(const char * playerTagName)
{
	Hero& hero = FindHero(playerTagName);

	for (std::vector<Resource>::iterator it = m_ResourcesOnMap.begin(); it != m_ResourcesOnMap.end(); it++)
	{
		if (it->GetPosition().X == hero.GetPosition().X && it->GetPosition().Y == hero.GetPosition().Y)
		{
			hero.TakeResourceField(*it);

			// remove the resource from the map;
			//std::string message = it->GetTagName();
			return "You got " + it->GetTagName() + " " + std::to_string(it->GetCounter());
		}
	}

	return std::string();
}
