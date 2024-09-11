#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <Color.hpp>

namespace Pathfinding
{
	struct Node;

	//	PATHFINDING
	bool NodeSort(Node* i, Node* j);
	bool ASort(Node* i, Node* j);
	void DrawPath(std::vector<Node*>& path, Color lineColour);
	float AHeuristic(Node* currentNode, Node* endNode, char h);
	std::vector<Node*> DijkstrasSearch(Node* startNode, Node* endNode);
	std::vector<Node*> AStarSearch(Node* startNode, Node* endNode);

	//	PATHING
	struct Edge {
		Node* target;
		float cost;

		Edge();
		Edge(Node& _target, float _cost);
		~Edge();

		//Node& GetTarget();
		void SetTarget(Node& newTarget);
	};

	struct Node {
		glm::vec2 m_position;
		std::vector<Edge> m_connections;
		float gScore;
		float hScore;
		float fScore;
		Node* previous;

		Node();
		Node(float x, float y);
		~Node();

		void ConnectTo(Node& other, float cost);
		Node& GetPrevious();
		void SetPrevious(Node& newPrevious);
	};

	class NodeMap {
		int m_width, m_height;
		float m_cellSize;

		Node** m_nodes;

	public:
		void Initialise(std::vector<std::string> asciiMap, int cellSize);
		Node* GetNode(int x, int y);
		void Draw();
		Node* GetClosestNode(glm::vec2 worldPos);

		Node* GetRandomNode();

		float GetCellSize() { return m_cellSize; }
	};
}
