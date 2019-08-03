#ifndef MESSAGE_H_GUARD
#define MESSAGE_H_GUARD

#include <Windows.h>
#include <chrono>

typedef std::chrono::time_point<std::chrono::system_clock> CurrentTime;

class Message
{
private:
	char* m_Message;
	COORD m_Position;
	CurrentTime m_Start;

public:
	Message(const char* message, const COORD& position, const CurrentTime& startTime) 
		:m_Position(position), m_Start(startTime)
	{
		size_t size = std::strlen(message) + 1;

		m_Message = new char[size];
		strcpy_s(m_Message, size, message);
	}

	Message(const Message& other) : m_Position(other.m_Position), m_Start(other.m_Start)
	{
		size_t size = std::strlen(other.m_Message) + 1;
		m_Message = new char[size];
		strcpy_s(m_Message, size, other.m_Message);
	}

	Message& operator=(const Message& rhs)
	{
		if (this != &rhs)
		{
			delete[] m_Message;

			size_t size = std::strlen(rhs.m_Message) + 1;

			m_Message = new char[size];
			strcpy_s(m_Message, size, rhs.m_Message);
			m_Position = rhs.m_Position;
			m_Start = rhs.m_Start;
		}

		return *this;
	}

	const char* GetAlert() const
	{
		return m_Message;
	}

	const COORD& GetPosition() const
	{
		return m_Position;
	}

	const CurrentTime& GetStartingTime() const
	{
		return m_Start;
	}
};

#endif