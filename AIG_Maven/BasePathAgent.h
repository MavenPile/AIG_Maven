#pragma once
#include <vector>
#include "glm/glm.hpp"

namespace Pathfinding
{
	struct Node;
	
	class BasePathAgent
	{
	public:
		glm::vec2 m_position;	//	current position in glm::vec2
		std::vector<Node*> m_path;	//	the path; a vector of nodes
		int m_currentTargetIndex;	//	the index of m_currentNode
		Node* m_currentTargetNode;	//	the node we're currently in/came from
		float m_speed;	//	agent speed/distance per second

	public:
		BasePathAgent();
		BasePathAgent(Node* startNode);

		void Update(float deltaTime);
		void GoToNode(Node* node);
		void Draw();

		std::vector<Node*> GetPath();
		const std::vector<Node*> GetPath() const;

		void SetSpeed(float speed) { m_speed = speed; }
	};
}