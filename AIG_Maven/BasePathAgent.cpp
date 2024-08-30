#include "BasePathAgent.h"
#include "Pathfinding.h"
#include <iostream>

using namespace AIForGames;

AIForGames::BasePathAgent::BasePathAgent() {
	m_currentNode = nullptr;
	m_speed = 0;
	m_position = glm::vec2(0, 0);
	m_currentIndex = 0;
}

AIForGames::BasePathAgent::BasePathAgent(Node* startNode, float speed) {
	m_currentNode = startNode;
	m_speed = speed;
	m_position = m_currentNode->m_position;
	m_currentIndex = 0;
}

void AIForGames::BasePathAgent::Update(float deltaTime) {
	//	If path is empty, return
	if (m_path.empty()) { std::cout << "Path empty..." << std::endl; return; }

	//	Calculate the distance to the next node and the unit vector to that node
	glm::vec2 dxdy = m_path[m_currentIndex + 1]->m_position - m_currentNode->m_position;
	float distToNext = sqrt(dxdy.x * dxdy.x + dxdy.y * dxdy.y);
	
	if (distToNext > 0) {	//	Normalise vector to next node
		glm::vec2 unitVector = dxdy / distToNext;
	}

	//	Subtract speed * deltaTime from the remaining distance to the next node
	float deltaDist = distToNext - m_speed * deltaTime;

	//	Check for overshoot
	if (deltaDist < 0)	//	We have overshot the node
	{
		m_currentIndex++;
		m_currentNode = m_path[m_currentIndex];

		//	Check if we've reached the final node
		if (m_currentNode == *m_path.end())	//	We've reached the final node
		{
			//	Snap position to node, and clear the path
			m_position = m_currentNode->m_position;
			m_path.clear();

			std::cout << "Reached final node..." << std::endl;
		}
		else	//	We have NOT reached the final node
		{
			//	Snap to node
			m_position = m_currentNode->m_position;
			
			//	Redirect remaining movement towards next node
			glm::vec2 newSToNode = m_currentNode->m_position - m_path[m_currentIndex + 1]->m_position;
			float newDToNode = sqrt(newSToNode.x * newSToNode.x + newSToNode.y * newSToNode.y);
			glm::vec2 newUnitVector = newSToNode / newDToNode;

			m_position += (0 - deltaDist) * newUnitVector;

			std::cout << "Changing direction..." << std::endl;
		}
	}
	else	//	We have NOT overshot the node
	{
		//	Move towards next node normally

		m_position += m_speed * deltaTime * unitVector;

		std::cout << "Travelling..." << std::endl;
	}
}

void AIForGames::BasePathAgent::GoToNode(Node* node) {
	m_path = DijkstrasSearch(m_currentNode, node);
	m_currentIndex = 0;
}

void AIForGames::BasePathAgent::Draw() {
	DrawCircle(m_position.x, m_position.y, 8, { 255,0,255,0 });
	std::cout << "Drawing Agent..." << std::endl;
}