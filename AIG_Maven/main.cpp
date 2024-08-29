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

	NodeMap map;
	vector<string> asciiMap;
	asciiMap.push_back("000000000000");
	asciiMap.push_back("010111011100");
	asciiMap.push_back("010101110110");
	asciiMap.push_back("010100000000");
	asciiMap.push_back("010111111110");
	asciiMap.push_back("010000001000");
	asciiMap.push_back("011111111110");
	asciiMap.push_back("000000000000");
	map.Initialise(asciiMap, 100);

	Node* start = map.GetNode(1, 1);
	Node* end = map.GetNode(10, 2);
	std::vector<Node*> nodeMapPath = DijkstrasSearch(start, end);
	Color lineColour = { 255,255,255,255 };

	//---	LOOP
	while (!WindowShouldClose())
	{
		//---	UPDATE


		//---	DRAW

		BeginDrawing();

		ClearBackground(DARKGRAY);

		if (IsMouseButtonPressed(0)) {
			Vector2 mousePos = GetMousePosition();
			start = map.GetClosestNode(glm::vec2(mousePos.x, mousePos.y));
			nodeMapPath = DijkstrasSearch(start, end);
		}
		else if (IsMouseButtonPressed(1)) {
			Vector2 mousePos = GetMousePosition();
			end = map.GetClosestNode(glm::vec2(mousePos.x, mousePos.y));
			nodeMapPath = DijkstrasSearch(start, end);
		}

		map.Draw();
		DrawPath(nodeMapPath, lineColour);

		EndDrawing();
	}

	//---	UNINITIALISE

	CloseWindow();

	return 0;
}