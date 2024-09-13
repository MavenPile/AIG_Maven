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
#include "Decisions.h"

using namespace Pathfinding;
using namespace std;
using namespace FSM;
using namespace Trees;

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
	asciiMap.push_back("00000000000000000000");
	asciiMap.push_back("01111101110011101110");
	asciiMap.push_back("01010111011110111110");
	asciiMap.push_back("01010000001010101000");
	asciiMap.push_back("01011111111010101110");
	asciiMap.push_back("01010000100010101110");
	asciiMap.push_back("01010111111110101110");
	asciiMap.push_back("01110100001011101110");
	asciiMap.push_back("01000111011001111110");
	asciiMap.push_back("01101101010000100000");
	asciiMap.push_back("01111101111111111110");
	asciiMap.push_back("0011101110000000010");
	asciiMap.push_back("00110000000111111110");
	asciiMap.push_back("00111011110111111110");
	asciiMap.push_back("00011110011111111110");
	asciiMap.push_back("00000000000000000000");

	map.Initialise(asciiMap, 50);

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

	//---	DECISION TREE

	TrueFalseDecision* within5 = new TrueFalseDecision();
	within5->AddCondition(new DistanceCondition(5.f * map.GetCellSize(), true));

	TrueFalseDecision* within1 = new TrueFalseDecision();
	within1->AddCondition(new DistanceCondition(1.f * map.GetCellSize(), true));

	BehaviourDecision* wanderLeaf = new BehaviourDecision();
	wanderLeaf->AddBehaviour(new WanderBehaviour());

	within5->AddTrue(within1);
	within5->AddFalse(wanderLeaf);

	BehaviourDecision* followLeaf = new BehaviourDecision();
	followLeaf->AddBehaviour(new FollowingBehaviour());

	BehaviourDecision* attackLeaf = new BehaviourDecision();
	attackLeaf->AddBehaviour(new AttackBehaviour(10,5));

	within1->AddTrue(attackLeaf);
	within1->AddFalse(followLeaf);

	//---	GENERATE AGENT

	//BasePathAgent agent(start, 100);

	//Agent dAgent(&map, new GoToPointBehaviour());
	//dAgent.SetNode(start);
	//dAgent.SetSpeed(100);

	Agent wAgent(&map, new WanderBehaviour());
	wAgent.SetNode(map.GetRandomNode());
	wAgent.SetSpeed(100);

	//Agent fAgent(&map, new SelectorBehaviour(new FollowingBehaviour(),new WanderBehaviour()));
	//fAgent.SetNode(map.GetRandomNode());
	//fAgent.SetStoredTarget(&wAgent);

	//Agent fsmAgent(&map, (Behaviour*)fsm);
	//fsmAgent.SetNode(map.GetRandomNode());
	//fsmAgent.SetStoredTarget(&wAgent);
	//fsmAgent.SetSpeed(50);

	//Agent uaiAgent(&map, utilityAI);
	//uaiAgent.SetNode(map.GetRandomNode());
	//uaiAgent.SetStoredTarget(&fsmAgent);
	//uaiAgent.SetSpeed(30);

	Agent dtAgent(&map, new DecisionBehaviour(within5));
	dtAgent.SetNode(map.GetRandomNode());
	dtAgent.SetSpeed(70);
	dtAgent.SetStoredTarget(&wAgent);

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
		//DrawPath(fAgent.GetBaseAgent()->m_path, { 255,255,0,255 });
		//DrawPath(fsmAgent.GetBaseAgent()->m_path, { 255,0,0,255 });
		//DrawPath(uaiAgent.GetBaseAgent()->m_path, { 0,255,0,255 });
		DrawPath(dtAgent.GetBaseAgent()->m_path, { 0,0,255,255 });

		//dAgent.Update(deltaTime);
		//dAgent.Draw();

		wAgent.Update(deltaTime);
		wAgent.Draw();

		//fAgent.Update(deltaTime);
		//fAgent.Draw();

		//fsmAgent.Update(deltaTime);
		//fsmAgent.Draw();

		//uaiAgent.Update(deltaTime);
		//uaiAgent.Draw();

		dtAgent.Update(deltaTime);
		dtAgent.Draw();

		EndDrawing();
	}

	//---	UNINITIALISE

	CloseWindow();

	system("pause");

	return 0;
}