#ifndef GAMEOBJECT_H_GUARD
#define GAMEOBJECT_H_GUARD

#include <Windows.h>
#include <string>

class GameObject
{
protected:
	std::string m_Tag;
	COORD m_Position;
	bool m_IsStatic;
	char m_Symbol;

protected:
	GameObject();
	GameObject(const std::string tag, const unsigned x, const unsigned y, bool isStatic, const char symbol);

public:
	virtual GameObject* GetObjectInstance() const = 0;


	std::string GetTagName() const
	{
		return m_Tag;
	}

	COORD GetPosition() const
	{
		return m_Position;
	}

	char GetObjectSymbol() const
	{
		return m_Symbol;
	}

	bool IsStatic() const
	{
		return m_IsStatic;
	}

	void SetStatic()
	{
		m_IsStatic = true;
	}

	void SetDynamic()
	{
		m_IsStatic = false;
	}
};

#endif