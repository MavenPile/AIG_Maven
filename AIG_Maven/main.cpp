#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS

//#include "raygui.h"
#include "Pathfinding.h"
#include <string>

using namespace AIForGames;
using namespace std;

int main()
{
	//---	INITIALISE

	int screenWidth = 1600;
	int screenHeight = 900;

	InitWindow(screenWidth, screenHeight, "AIG");

	SetTargetFPS(60);

	//---

	vector<string> asciiMap;
	asciiMap.push_back("000000000000");
	asciiMap.push_back("010111011100");
	asciiMap.push_back("010101110110");
	asciiMap.push_back("010100000000");
	asciiMap.push_back("010111111110");
	asciiMap.push_back("010000001000");
	asciiMap.push_back("011111111110");
	asciiMap.push_back("000000000000");

	NodeMap map;
	map.Initialise(asciiMap, 100);

	//---	LOOP
	while (!WindowShouldClose())
	{
		//---	UPDATE



		//---	DRAW

		BeginDrawing();

		ClearBackground(RAYWHITE);
		DrawText("This is your window!", 190, 200, 20, LIGHTGRAY);
		map.Draw();

		EndDrawing();
	}

	//---	UNINITIALISE

	CloseWindow();

	return 0;
}