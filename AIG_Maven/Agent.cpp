#include "Agent.h"
#include "Behaviour.h"
#include "BasePathAgent.h"
#include "Pathfinding.h"

using namespace Pathfinding;

namespace Decision
{
	void Agent::Update(float deltaTime)
	{
		if (m_current)	{
			m_current->Update(this, deltaTime);
		}
		m_pathAgent.Update(deltaTime);
	}

	void Agent::Draw()
	{
		m_pathAgent.Draw();
	}

	void Agent::GoTo(glm::vec2 point)
	{
		Node* end = m_nodeMap->GetClosestNode(point);
		m_pathAgent.GoToNode(end);
	}

	NodeMap* Agent::GetPath()
	{
		return m_nodeMap;
	}

	void Agent::SetStartNode(Node* startNode)
	{
		m_pathAgent.m_currentTargetNode = startNode;
	}
}