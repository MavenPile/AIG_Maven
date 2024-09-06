#include "GoToPointBehaviour.h"
#include "raylib-cpp.hpp"
#include "Agent.h"

void GoToPointBehaviour::Update(Agent* agent, float deltaTime)
{
	//	Read mouseclicks, left for start node, right for end node
	if (IsMouseButtonPressed(0))
	{
		Vector2 mousePos = GetMousePosition();
		agent->GoTo(glm::vec2(mousePos.x, mousePos.y));
	}
}