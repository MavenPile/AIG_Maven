#include "BasePathAgent.h"
#include "Pathfinding.h"
#include <iostream>

namespace AIForGames
{
	AIForGames::BasePathAgent::BasePathAgent() {
		m_currentNode = nullptr;
		m_targetNode = nullptr;
		m_speed = 0;
		m_position = glm::vec2(0, 0);
		m_currentIndex = 0;
	}

	AIForGames::BasePathAgent::BasePathAgent(Node* startNode, float speed) {
		m_currentNode = startNode;
		m_targetNode = nullptr;
		m_speed = speed;
		m_position = m_currentNode->m_position;
		m_currentIndex = 0;
	}

	void AIForGames::BasePathAgent::Update(float deltaTime) {
		//	If path is empty, return
		if (m_path.empty()) { /*std::cout << "Path empty..." << std::endl;*/ return; }

		//	If there's no target node, update
		if (m_targetNode == nullptr) { m_targetNode = m_path[m_currentIndex + 1]; }

		//	Calculate the distance to the target node
		glm::vec2 dxdy = m_targetNode->m_position - m_position;
		float distToNext = sqrt(dxdy.x * dxdy.x + dxdy.y * dxdy.y);

		//	Find unit vector to target node
		glm::vec2 dxdyNormal;
		if (distToNext > 0) {	//	Normalise vector to target node
			dxdyNormal = dxdy / distToNext;
		}

		//	Subtract speed * deltaTime from the remaining distance to the target node
		float deltaDist = distToNext - m_speed * deltaTime;

		//	Check for overshoot
		if (deltaDist < 0)	//	We have overshot the target node
		{
			m_currentIndex++;
			m_currentNode = m_targetNode;

			//	Check if we've reached the final node
			if (m_currentIndex >= m_path.size())	//	We've reached the final node
			{
				//	Snap position to node, and clear the path
				m_position = m_currentNode->m_position;
				m_targetNode = nullptr;
				m_path.clear();

				std::cout << "Reached final node..." << std::endl;
			}
			else	//	We have NOT reached the final node
			{
				std::cout << "Reached a node..." << std::endl;
				
				//	Set a new target node
				m_targetNode = m_path[m_currentIndex + 1];
				std::cout << "Next node position: X: " << m_targetNode->m_position.x << ", Y: " << m_targetNode->m_position.y << std::endl;

				//	Calculate distance to target node from new current node
				dxdy = m_targetNode->m_position - m_currentNode->m_position;
				std::cout << "Difference to next: " << dxdy.x << " " << dxdy.y << std::endl;
				distToNext = sqrt(dxdy.x * dxdy.x + dxdy.y * dxdy.y);
				std::cout << "Distance to next: " << distToNext << std::endl;

				//	Calculate unit vector to target node
				dxdyNormal = dxdy / distToNext;

				//	Move agent to new position
				m_position = m_targetNode->m_position - distToNext * dxdyNormal;
				std::cout << "New position: X: " << m_position.x << ", Y: " << m_position.y << std::endl;





				//	Redirect remaining movement towards next node
				//glm::vec2 newSToNode = m_currentNode->m_position - m_path[m_currentIndex + 1]->m_position;
				//float newDToNode = sqrt(newSToNode.x * newSToNode.x + newSToNode.y * newSToNode.y);
				//glm::vec2 newUnitVector = newSToNode / newDToNode;

				//dxdy = m_currentNode->m_position - m_path[m_currentIndex + 1]->m_position;

				//m_position += (0 - deltaDist) * newUnitVector;
			}
		}
		else	//	We have NOT overshot the node
		{
			//	Move towards next node normally

			m_position += m_speed * deltaTime * dxdyNormal;

			//std::cout << "Travelling..." << std::endl;
		}
	}

	void AIForGames::BasePathAgent::GoToNode(Node* node) {
		m_path = DijkstrasSearch(m_currentNode, node);
		m_currentIndex = 0;
	}

	void AIForGames::BasePathAgent::Draw() {
		DrawCircle(m_position.x, m_position.y, 50, { 255,255,0,255 });
		//std::cout << "Drawing Agent..." << std::endl;
	}

	std::vector<Node*> AIForGames::BasePathAgent::GetPath() { return m_path; }

	const std::vector<Node*> AIForGames::BasePathAgent::GetPath() const { return m_path; }

}