#ifndef GAMEOBJECTHANDLER_H_GUARD
#define GAMEOBJECTHANDLER_H_GUARD

#include "GameObject.h"

class GameObjectHandler
{
private:
	GameObject* m_Handler;

public:
	GameObjectHandler();
	GameObjectHandler(const GameObject&);
	GameObjectHandler(const GameObjectHandler&);
	~GameObjectHandler();

	GameObjectHandler& operator=(const GameObjectHandler&);
};

#endif