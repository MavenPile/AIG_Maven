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
		std::cout << "Entering Wander Behaviour..." << std::endl;
		agent->SetColour({ 0,0,255,255 });
		//	We don't want to reset the path when entering a wandering behaviour,
		//because the agent should still go to where it last tried to pathfind
		//to. For example, it may have come from a following behaviour, in which
		//case, it would want to go to where it last "saw" the player.
		//agent->Reset();
	}

	float WanderBehaviour::Evaluate(Agent* agent) {
		Agent* target = agent->GetStoredTarget();
		float dist = glm::distance(target->GetPosition(), agent->GetPosition());

		float eval = dist;
		if (eval < 0) {
			eval = 0;
		}

		return eval;
	}

	void GoToPointBehaviour::Update(Agent* agent, float deltaTime)	{
		//	Read mouseclicks, left for start node, right for end node
		if (IsMouseButtonPressed(0))
		{
			//std::cout << "Mouse button 0 pressed..." << std::endl;
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
		std::cout << "Entering Follow Behaviour..." << std::endl;
		agent->SetColour({ 255,0,0,255 });
		agent->Reset();
	}

	float FollowingBehaviour::Evaluate(Agent* agent)	{
		Agent* target = agent->GetStoredTarget();
		float dist = glm::distance(target->GetPosition(), agent->GetPosition());

		float eval = 10 * agent->GetMap()->GetCellSize() - dist;
		if (eval < 0) {
			eval = 0;
		}

		return eval;
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
