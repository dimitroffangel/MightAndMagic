#include "Drawing.h"

HANDLE DrawingObject::HConsole = NULL;
unsigned DrawingObject::WIDTH = 1;
unsigned DrawingObject::HEIGHT = 1;

void DrawingObject::DrawObject(HANDLE& hConsole, const char * character, COORD position, DWORD dwBytesWritten)
{
	WriteConsoleOutputCharacter(hConsole, character, std::strlen(character), position, &dwBytesWritten);
}

void DrawingObject::DrawMap(const Map& map)
{
	vectorString objectsToDraw = map.GetObjectsToDraw();

	for (vectorString::const_iterator cit = objectsToDraw.cbegin(); cit != objectsToDraw.cend(); cit++)
	{
		COORD position;
		position.X = 0;
		position.Y = cit - objectsToDraw.cbegin();
		DWORD dwBytesWritten = 0;

		const char* row = cit->c_str();
		DrawObject(DrawingObject::HConsole, row, position, dwBytesWritten);
	}

	// all objects have location, the function only have to draw it...
}

void DrawingObject::WipeMeshes(const Map & map)
{
	vectorString objectsToDraw = map.GetObjectsToDraw();

	size_t rowLength = map.GetMapWidth();

	char* row = new char[rowLength + 1];

	for (size_t i = 0; i < rowLength; i++)
		row[i] = ' ';

	row[rowLength] = '\0';

	for (vectorString::const_iterator cit = objectsToDraw.cbegin(); cit != objectsToDraw.cend(); cit++)
	{
		COORD position;
		position.X = 0;
		position.Y = cit - objectsToDraw.cbegin();
		DWORD dwBytesWritten = 0;

		DrawObject(DrawingObject::HConsole, row, position, dwBytesWritten);
	}

	delete[] row;
}
