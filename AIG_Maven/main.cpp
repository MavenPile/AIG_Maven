#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS

#include "Pathfinding.h"
#include <string>
#include "BasePathAgent.h"
#include "Agent.h"
#include "Behaviours.h"

using namespace Pathfinding;
using namespace std;
using namespace Decision;

int main()
{
	//---	INITIALISE

	int screenWidth = 1600;
	int screenHeight = 900;

	InitWindow(screenWidth, screenHeight, "AI For Games");

	SetTargetFPS(60);

	//---	GENERATE MAP

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
	std::vector<Node*> nodeMapPath = AStarSearch(start, end);
	Color lineColour = { 255,255,255,255 };

	//---	GENERATE AGENT

	//BasePathAgent agent(start, 100);

	Agent dAgent(&map, new GoToPointBehaviour());
	dAgent.SetNode(start);

	Agent wAgent(&map, new WanderBehaviour());
	wAgent.SetNode(end);

	//---	LOOP

	float deltaTime;

	while (!WindowShouldClose())
	{
		deltaTime = GetFrameTime();		

		//---	UPDATE



		//---	DRAW

		BeginDrawing();

		ClearBackground(DARKGRAY);

		map.Draw();
		//DrawPath(nodeMapPath, lineColour);
		DrawPath(dAgent.GetBaseAgent()->m_path, lineColour);

		//if (IsMouseButtonPressed(0)) {
		//	Vector2 mousePos = GetMousePosition();
		//	//start = map.GetClosestNode(glm::vec2(mousePos.x, mousePos.y));
		//	//nodeMapPath = DijkstrasSearch(start, end);
		//	Node* end = map.GetClosestNode(glm::vec2(mousePos.x,mousePos.y));
		//	agent.GoToNode(end);
		//}

		dAgent.Update(deltaTime);
		dAgent.Draw();

		wAgent.Update(deltaTime);
		wAgent.Draw();

		EndDrawing();
	}

	//---	UNINITIALISE

	CloseWindow();

	system("pause");

	return 0;
}