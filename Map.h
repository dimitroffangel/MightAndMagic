#ifndef MAP_H_GUARD
#define MAP_H_GUARD

#include "HeroHandler.h"

typedef std::vector< std::string > vectorString;

class Map
{
private:
	vectorString m_ObjectsDesignOnMap;
	std::vector<HeroHandler> m_HeroesOnMap;
	std::vector<Resource> m_ResourcesOnMap;
	const unsigned m_MapWidth;
	const unsigned m_MapHeight;

public:
	Map();
	Map(const unsigned mapWidth, const unsigned mapHeight);
	
	void UpdateChanges(); // TODO the bot logic...
	void AddResource(const Resource& resource);
	void AddHero(const Hero& hero);
	void RemoveHero(const std::string tag);
	Hero& FindHero(const std::string tag);
	std::string TryPlayerGettingResource(const char* playerTagName);
	const unsigned GetMapWidth() const
	{
		return m_MapWidth;
	}

	vectorString GetObjectsToDraw() const
	{
		return m_ObjectsDesignOnMap;
	}
};

#endif