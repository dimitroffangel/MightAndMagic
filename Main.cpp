#include <iostream>
#include <chrono>
#include <vector>

#include "Engine.h"
#include "Balfur.h"


int main()
{
	Engine engine(10, 10);
	engine.BeforeStartingGame();
	engine.OnEachFrame();


/*
	COORD position = { x,y };
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	const char* str = "Some text";
	DWORD len = std::strlen(str);
	DWORD dwBytesWritten = 0;
	WriteConsoleOutputCharacter(hConsole, str, len, position, &dwBytesWritten);
	
	player.MoveOnTurn(3, 3);
	*/

	return 0;
}