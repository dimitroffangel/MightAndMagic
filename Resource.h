#ifndef RESOURCE_H_GUARD
#define RESOURCE_H_GUARD

#include "GameObject.h"

class Resource : public GameObject
{
protected:
	std::string m_Name;
	unsigned m_Counter;

public:
	Resource();
	Resource(const char* tag, const unsigned x, const unsigned y, bool isStatic, const char symbol
			,const std::string name, const unsigned counter);
	~Resource();

	virtual GameObject* GetObjectInstance() const override;

	std::string GetName() const
	{
		return m_Name;
	}

	unsigned GetCounter() const
	{
		return m_Counter;
	}
};

#endif