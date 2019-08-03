#include "GameObject.h"


GameObject::GameObject()
{

}

GameObject::GameObject(const std::string tag, const unsigned x, const unsigned y, bool isStatic, const char symbol)
{
	m_Tag = tag;
	m_Position.X = x;
	m_Position.Y = y;
	m_IsStatic = isStatic;
	m_Symbol = symbol;
}