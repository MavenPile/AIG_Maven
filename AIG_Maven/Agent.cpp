#include "Agent.h"
#include "Behaviour.h"
#include "BasePathAgent.h"
#include "Pathfinding.h"
#include <iostream>

using namespace Pathfinding;

namespace FSM
{
	Agent::Agent(NodeMap* _nodeMap, Behaviour* _behaviour) : m_current(_behaviour), m_nodeMap(_nodeMap), m_colour({ 255,255,0,255 })	{
		m_current->Enter(this);
	}

	void Agent::Update(float deltaTime)
	{
		if (m_current)	{
			m_current->Update(this, deltaTime);
		}
		m_pathAgent.Update(deltaTime);
	}

	void Agent::Draw()
	{
		//m_pathAgent.Draw();
		DrawCircle(m_pathAgent.m_position.x, m_pathAgent.m_position.y, 20, m_colour);
	}

	void Agent::GoTo(glm::vec2 point)
	{
		Node* end = m_nodeMap->GetClosestNode(point);
		m_pathAgent.GoToNode(end);
	}

	void Agent::SetNode(Node* node)
	{
		m_pathAgent.m_currentTargetNode = node;
		m_pathAgent.m_position = node->m_position;
	}

	BasePathAgent* Agent::GetBaseAgent()
	{
		return &m_pathAgent;
	}

	bool Agent::PathComplete()
	{
		if (m_pathAgent.GetPath().empty())
		{
			std::cout << "Verified path is complete..." << std::endl;
		}

		return m_pathAgent.GetPath().empty();
	}

	NodeMap* Agent::GetMap()
	{
		return m_nodeMap;
	}
}