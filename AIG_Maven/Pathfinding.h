#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace AIForGames
{
	struct Node;

	struct Edge {
		Node* target;
		float cost;

		Edge() { target = nullptr; cost = 0; }
		Edge(Node& _target, float _cost) : target(&_target), cost(_cost) {}
	};

	struct Node {
		glm::vec2 m_position;
		std::vector<Edge> m_connections;

		Node() { m_position.x = 0; m_position.y = 0; }
		Node(float x, float y) { m_position.x = x; m_position.y = y; }
		~Node() {}

		void ConnectTo(Node& other, float cost) {
			m_connections.push_back(Edge(other, cost));
		}
	};
}
