#pragma once
#include <vector>
#include "glm/glm.hpp"

namespace AIForGames
{
	struct Node;
	
	class BasePathAgent
	{
			glm::vec2 m_position;

			std::vector<Node*> m_path;
			int m_currentIndex;
			Node* m_currentNode;

			float m_speed;

		public:
			BasePathAgent();
			BasePathAgent(Node* startNode, float speed);

			void Update(float deltaTime);
			void GoToNode(Node* node);
			void Draw();
	};
}