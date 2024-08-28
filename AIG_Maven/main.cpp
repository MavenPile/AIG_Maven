#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS

//#include "raygui.h"
#include "Pathfinding.h"
//#include "cstring.h"

using namespace AIForGames;

int main()
{
	//---	INITIALISE

	int screenWidth = 1600;
	int screenHeight = 900;

	InitWindow(screenWidth, screenHeight, "AIG");

	SetTargetFPS(60);

	//---


	//---	LOOP
	while (!WindowShouldClose())
	{
		//---	UPDATE



		//---	DRAW

		BeginDrawing();

		ClearBackground(RAYWHITE);
		DrawText("This is your window!", 190, 200, 20, LIGHTGRAY);

		EndDrawing();
	}

	//---	UNINITIALISE

	CloseWindow();

	return 0;
}