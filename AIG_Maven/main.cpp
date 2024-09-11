#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS

#include "Pathfinding.h"
#include <string>
#include "BasePathAgent.h"
#include "Agent.h"
#include "Behaviours.h"
#include "Conditions.h"
#include "FiniteStateMachine.h"
#include "UtilityAI.h"

using namespace Pathfinding;
using namespace std;
using namespace FSM;

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

	//---	FINITE STATE MACHINE

	DistanceCondition* closerThan5 = new DistanceCondition(5.0f * map.GetCellSize(), true);
	DistanceCondition* furtherThan7 = new DistanceCondition(7.0f * map.GetCellSize(), false);

	State* wanderState = new State(new WanderBehaviour());
	State* followState = new State(new FollowingBehaviour());

	wanderState->AddTransition(closerThan5, followState);
	followState->AddTransition(furtherThan7, wanderState);

	FiniteStateMachine* fsm = new FiniteStateMachine(wanderState);
	fsm->AddState(wanderState);
	fsm->AddState(followState);

	//---	UTILITYAI

	UtilityAI* utilityAI = new UtilityAI();
	utilityAI->AddBehaviour(new WanderBehaviour());
	utilityAI->AddBehaviour(new FollowingBehaviour());

	//---	GENERATE AGENT

	//BasePathAgent agent(start, 100);

	//Agent dAgent(&map, new GoToPointBehaviour());
	//dAgent.SetNode(start);
	//dAgent.SetSpeed(100);

	Agent wAgent(&map, new WanderBehaviour());
	wAgent.SetNode(start);
	wAgent.SetSpeed(100);

	//Agent fAgent(&map, new SelectorBehaviour(new FollowingBehaviour(),new WanderBehaviour()));
	//fAgent.SetNode(start);
	//fAgent.SetStoredTarget(&wAgent);

	Agent fsmAgent(&map, (Behaviour*)fsm);
	fsmAgent.SetNode(map.GetRandomNode());
	fsmAgent.SetStoredTarget(&wAgent);
	fsmAgent.SetSpeed(50);

	Agent uaiAgent(&map, utilityAI);
	uaiAgent.SetNode(end);
	uaiAgent.SetStoredTarget(&fsmAgent);
	uaiAgent.SetSpeed(30);

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

		//if (IsMouseButtonPressed(0)) {
		//	Vector2 mousePos = GetMousePosition();
		//	//start = map.GetClosestNode(glm::vec2(mousePos.x, mousePos.y));
		//	//nodeMapPath = DijkstrasSearch(start, end);
		//	Node* end = map.GetClosestNode(glm::vec2(mousePos.x,mousePos.y));
		//	agent.GoToNode(end);
		//}

		DrawPath(wAgent.GetBaseAgent()->m_path, { 255,255,255,255 });
		DrawPath(fsmAgent.GetBaseAgent()->m_path, { 255,0,0,255 });
		DrawPath(uaiAgent.GetBaseAgent()->m_path, { 0,255,0,255 });

		//dAgent.Update(deltaTime);
		//dAgent.Draw();

		wAgent.Update(deltaTime);
		wAgent.Draw();

		//fAgent.Update(deltaTime);
		//fAgent.Draw();

		fsmAgent.Update(deltaTime);
		fsmAgent.Draw();

		uaiAgent.Update(deltaTime);
		uaiAgent.Draw();

		EndDrawing();
	}

	//---	UNINITIALISE

	CloseWindow();

	system("pause");

	return 0;
}