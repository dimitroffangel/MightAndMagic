#include "GameObjectHandler.h"



GameObjectHandler::GameObjectHandler() : m_Handler(nullptr)
{

}

GameObjectHandler::GameObjectHandler(const GameObject & gameObject)
{
	m_Handler = gameObject.GetObjectInstance();
}

GameObjectHandler::GameObjectHandler(const GameObjectHandler & other)
{
	if (other.m_Handler)
		m_Handler = other.m_Handler->GetObjectInstance();
}


GameObjectHandler::~GameObjectHandler()
{
	delete m_Handler;
}

GameObjectHandler & GameObjectHandler::operator=(const GameObjectHandler& rhs) 
{
	if (this != &rhs)
	{
		if (m_Handler)
			delete m_Handler;

		if (rhs.m_Handler)
			m_Handler = rhs.m_Handler->GetObjectInstance();

		else
			m_Handler = nullptr;
	}

	return *this;
}
