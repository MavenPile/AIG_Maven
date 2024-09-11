#include "Behaviours.h"
#include "Pathfinding.h"
#include "Agent.h"
#include <iostream>

namespace FSM
{
	void WanderBehaviour::Update(Agent* agent, float deltaTime)	{
		if (agent->PathComplete()) {
			std::cout << "Path complete, finding random node..." << std::endl;
			
			glm::vec2 ranNode = agent->GetMap()->GetRandomNode()->m_position;
			agent->GoTo(ranNode);
		}
	}

	void WanderBehaviour::Enter(Agent* agent) {
		//	Blue when wandering
		agent->SetColour({ 0,0,255,255 });
		agent->Reset();
	}

	void GoToPointBehaviour::Update(Agent* agent, float deltaTime)	{
		//	Read mouseclicks, left for start node, right for end node
		if (IsMouseButtonPressed(0))
		{
			std::cout << "Mouse button 0 pressed..." << std::endl;
			Vector2 mousePos = GetMousePosition();
			agent->GoTo(glm::vec2(mousePos.x, mousePos.y));
		}
	}

	void FollowingBehaviour::Update(Agent* agent, float deltaTime)	{
		//	Check if the agent has moved significantly from its last position
		//	If so we want to repath towards it
		Agent* target = agent->GetStoredTarget();

		float dist = glm::distance(target->GetPosition(),m_lastTargetPosition);

		if (dist > agent->GetMap()->GetCellSize()) {
			m_lastTargetPosition = target->GetPosition();
			agent->GoTo(m_lastTargetPosition);
		}
	}

	void FollowingBehaviour::Enter(Agent* agent)	{
		//	Red when following
		agent->SetColour({ 255,0,0,255 });
		agent->Reset();
	}

	void SelectorBehaviour::Update(Agent* agent, float deltaTime)	{
		if (glm::distance(agent->GetPosition(), agent->GetStoredTarget()->GetPosition()) < agent->GetMap()->GetCellSize() * 5)	{
			SetBehaviour(m_b1, agent);
			agent->SetColour({ 255,0,0,255 });
		}
		else	{
			SetBehaviour(m_b2, agent);
			agent->SetColour({ 0,255,255,255 });
		}
		m_selected->Update(agent, deltaTime);
	}

	void SelectorBehaviour::SetBehaviour(Behaviour* b, Agent* agent)	{
		if (m_selected != b)
	{
			m_selected = b;
			agent->Reset();
		}
	}
}
