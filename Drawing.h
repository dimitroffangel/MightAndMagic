#ifndef DRAWING_H_GUARD
#define DRAWING_H_GUARD

#include "Map.h"

#include <Windows.h>

class DrawingObject
{
public:
	DrawingObject() = delete;

	static HANDLE HConsole;	
	static unsigned WIDTH;
	static unsigned HEIGHT;

	static void DrawObject(HANDLE&, const char*, const COORD, DWORD);
	static void DrawMap(const Map& map);
	static void WipeMeshes(const Map& map);
};


#endif
