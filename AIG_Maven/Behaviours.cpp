#include "Behaviours.h"
#include "Pathfinding.h"
#include "Agent.h"
#include <iostream>

namespace Decision
{
	void WanderBehaviour::Update(Agent* agent, float deltaTime)
	{
		if (agent->PathComplete()) {
			std::cout << "Path complete, finding random node..." << std::endl;
			
			glm::vec2 ranNode = agent->GetMap()->GetRandomNode()->m_position;
			agent->GoTo(ranNode);
		}
	}

	void GoToPointBehaviour::Update(Agent* agent, float deltaTime)
	{
		//	Read mouseclicks, left for start node, right for end node
		if (IsMouseButtonPressed(0))
		{
			std::cout << "Mouse button 0 pressed..." << std::endl;
			Vector2 mousePos = GetMousePosition();
			agent->GoTo(glm::vec2(mousePos.x, mousePos.y));
		}
	}

	void FollowingBehaviour::Update(Agent* agent, float deltaTime)
	{
		//	Check if the agent has moved significantly from its last position
		//	If so we want to repath towards it
		Agent* target;

		float dist;
		if (dist > agent->GetMap()->GetCellSize()) {
			m_lastTargetPosition = target->GetPosition();
			agent->GoTo(m_lastTargetPosition);
		}
	}
}
