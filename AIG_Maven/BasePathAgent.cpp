#include "BasePathAgent.h"
#include "Pathfinding.h"
#include <iostream>

namespace Pathfinding
{
	BasePathAgent::BasePathAgent() {
		m_currentTargetNode = nullptr;
		m_speed = 0;
		m_position = glm::vec2(0, 0);
		m_currentTargetIndex = 0;
	}

	BasePathAgent::BasePathAgent(Node* startNode) {
		m_currentTargetNode = startNode;
		m_speed = 100;
		m_position = m_currentTargetNode->m_position;
		m_currentTargetIndex = 0;
	}

	void BasePathAgent::Update(float deltaTime) {
		//	If path is empty, return
		if (m_path.empty()) { /*std::cout << "Path empty..." << std::endl;*/ return; }

		//	Calculate the distance to the target node
		glm::vec2 dispToNext = m_path[m_currentTargetIndex]->m_position - m_position;	//	Vector
		float distToNext = sqrt(dispToNext.x * dispToNext.x + dispToNext.y * dispToNext.y);	//	Magnitude


		distToNext = glm::distance(m_position, m_path[m_currentTargetIndex]->m_position);

		//	Find unit vector to target node
		//glm::vec2 dispNormal = dispToNext / distToNext;	//	Vector divided by magnitude
		
		glm::vec2 dispNormal = glm::normalize(dispToNext);

		if (glm::isnan(dispNormal.x))
		{
			dispNormal = glm::vec2(0, 0);
		}

		//	Subtract speed * deltaTime from the remaining distance to the target node
		float frameMovement = distToNext - m_speed * deltaTime;	//	Frame movement

		//std::cout << frameMovement << std::endl;

		//	Check for overshoot
		if (frameMovement < 0.f)	//	We have overshot the target node
		{
			//std::cout << "Overshot Node..." << std::endl;
			
			m_currentTargetIndex++;

			//std::cout << "Target Index: " << m_currentTargetIndex << std::endl;
			//std::cout << "Path Length: " << m_path.size() << std::endl;

			//	Check if we've reached the final node
			if (m_currentTargetIndex >= m_path.size())	//	We've reached the final node
			{
				//std::cout << "Reached final node..." << std::endl;

				//	Snap position to node, and clear the path
				m_position = m_currentTargetNode->m_position;
				m_path.clear();
			}
			else	//	We have NOT reached the final node
			{
				//std::cout << "Reached a node..." << std::endl;
				
				m_currentTargetNode = m_path[m_currentTargetIndex];

				//	Calculate distance to target node from new current node
				dispToNext = m_currentTargetNode->m_position - m_position;
				//std::cout << "Difference to next: " << dispToNext.x << " " << dispToNext.y << std::endl;
				distToNext = sqrt(dispToNext.x * dispToNext.x + dispToNext.y * dispToNext.y);
				//std::cout << "Distance to next: " << distToNext << std::endl;

				//	Calculate unit vector to target node
				dispNormal = dispToNext / distToNext;

				//	Move agent to new position
				m_position = m_currentTargetNode->m_position - distToNext * dispNormal;
				//std::cout << "New position: X: " << m_position.x << ", Y: " << m_position.y << std::endl;
			}
		}
		else	//	We have NOT overshot the node
		{
			//	Move towards next node normally

			m_position += m_speed * deltaTime * dispNormal;

			//std::cout << "Travelling..." << std::endl;
		}
	}

	void BasePathAgent::GoToNode(Node* node) {
		m_path = DijkstrasSearch(m_currentTargetNode, node);
		m_currentTargetIndex = 0;
	}

	void BasePathAgent::Draw() {
		DrawCircle(m_position.x, m_position.y, 50, { 255,255,0,255 });
		//std::cout << "Drawing Agent..." << std::endl;
	}

	std::vector<Node*> BasePathAgent::GetPath() { return m_path; }

	const std::vector<Node*> BasePathAgent::GetPath() const { return m_path; }
}