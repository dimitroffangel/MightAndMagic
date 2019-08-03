#include "Resource.h"



Resource::Resource()
{
}

Resource::Resource(const char* tag, const unsigned x, const unsigned y, bool isStatic, const char symbol, 
	const std::string name, const unsigned counter) :GameObject(tag, x, y, isStatic, symbol)
{
	m_Name = name;
	m_Counter = counter;
}


Resource::~Resource()
{
}

GameObject * Resource::GetObjectInstance() const
{
	return new Resource(*this);
}
