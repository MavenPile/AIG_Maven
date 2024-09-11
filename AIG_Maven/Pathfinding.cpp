#include "Pathfinding.h"
#include <iostream>
#include <algorithm>

using namespace std;

namespace Pathfinding
{
	bool NodeSort(Node* i, Node* j) {
		return (i->gScore < j->gScore);
	}

	bool ASort(Node* i, Node* j) {
		return (i->fScore < j->fScore);
	}

	void DrawPath(std::vector<Node*>& path, Color lineColour) {
		for (int i = 1; i < path.size(); i++) {
			DrawLine(path[i - 1]->m_position.x, path[i - 1]->m_position.y, path[i]->m_position.x, path[i]->m_position.y, lineColour);
		}
	}

	float AHeuristic(Node* currentNode, Node* endNode, char h)
	{
		float dx;
		float dy;
		glm::vec2 disp;

		//	A switch statement so we can use different heuristics
		switch (h) {
		case 'm':
			//	Manhattan Distance Heuristic
			//	Because it leads to better pathing in grid-based maps, like
			//the one being done for this assignment.

			//	Difference in x and difference in y
			dx = endNode->m_position.x - currentNode->m_position.x;
			dy = endNode->m_position.y - currentNode->m_position.y;

			//	Return the sum of calculations
			return dx + dy;
			break;
		default:
			//	Regular Distance Heuristic
			//	Measures distance between current and target node

			//	The displacement between the nodes
			disp = endNode->m_position - currentNode->m_position;

			//	The squared distance between the nodes
			return disp.x * disp.x + disp.y * disp.y;
			//	Square rooting the value would be expensive and unecessary, we can avoid it in this case
			break;
		}
	}

	std::vector<Node*> DijkstrasSearch(Node* startNode, Node* endNode)
	{
		//	Validate the input
		if (startNode == nullptr) {	//	If startNode is null OR endNode is NULL
			//	Raise error
			cout << "Search Validation Error: startNode is not valid." << endl;
			return vector<Node*>();
		}
		else if (endNode == nullptr) {
			cout << "Search Validation Error: endNode is not valid." << endl;
			return vector<Node*>();
		}

		if (&startNode == &endNode) {	//	If startNode == endNode
			//	Return empty path
			vector<Node*> emptyPath;
			emptyPath.push_back(startNode);
			return emptyPath;
		}

		//	Initialise the starting node
		startNode->gScore = 0;
		startNode->previous = nullptr;

		//	Create our temporary lists for storing nodes we're visiting/visited
		vector<Node*> openList;
		vector<Node*> closedList;

		//	Add startNode to openList
		openList.push_back(startNode);

		//	While openList is not empty
		while (!openList.empty()) {
			//	Sort openList based on gScore
			sort(openList.begin(), openList.end(), NodeSort);

			Node* currentNode = *openList.begin();

			//	If we visit the endNode, then we can exit early.
			//	Sorting the openList above guarantees the shortest path is found,
			//given no negative costs (a prerequisite of the algorithm).
			//	This is an optional optimisation that improves performance,
			//but doesn't always guarantee the shortest path.
			//if (currentNode == &endNode)
			//{
			//	break;
			//}

			//	Remove currentNode from openList
			openList.erase(openList.begin());

			//	Add currentNode to closedList
			closedList.push_back(currentNode);

			//	For all connections c in currentNode
			for (Edge c : currentNode->m_connections) {
				//	If target is in closedList
				if (find(closedList.begin(), closedList.end(), c.target) != closedList.end()) {
					//	Don't process target, it has already been processed.
					continue;
				}

				//	Calculate the gScore for the target.
				float gScore = currentNode->gScore + c.cost;

				//	If target is not in openList, process target.
				if (find(openList.begin(), openList.end(), c.target) == openList.end()) {
					//	This target has not been visited, so we must
					//update its gScore to the value we've calculated,
					//update its parent, and add it to the openList.
					c.target->gScore = gScore;
					c.target->SetPrevious(*currentNode);
					openList.push_back(c.target);

					//	Sort the list to keep all nodes in the appropriate
					//position while processing all currentNode edges.
					//	Keeping the openList sorted prioritises nodes with
					//the lowest gScore.
					//sort(openList.begin(), openList.end(), NodeSort);
				}
				//	Target is already in the openList with a valid gScore.
				//	So compare the calculated gScore with the existing
				//to find the shorter path.
				else if (currentNode->gScore < c.target->gScore) {
					c.target->gScore = currentNode->gScore;
					c.target->SetPrevious(*currentNode);
				}

				//if (find(openList.begin(), openList.end(), c.GetTarget()) == openList.end())	//	if c.target is not in open list
				//	//	std::find returns last/end() if it cannot find the target
				//{
				//	//	Let gScore = currentNode.gScore + c.cost
				//	float gScore = currentNode->gScore + c.cost;

				//	//	Have not yet visited the node.
				//	//	So calculate the Score and update its parent.
				//	//	Also add it to the openList for processing.
				//	if (find(closedList.begin(), closedList.end(), c.GetTarget()) == closedList.end())	//	if c.target is not in closed list
				//	{
				//		c.target->gScore = gScore;
				//		c.target->SetPrevious(*currentNode);
				//		openList.push_back(&c.GetTarget());
				//	}
				//	//	Node is already in the openList with a valid gScore.
				//	//	So compare the calculated gScore with the existing
				//	//to find the shorter path.
				//	else if (currentNode->gScore < c.target->gScore)	//	Else if (gScore < c.target.gScore)
				//	{
				//		c.target->gScore = gScore;
				//		c.target->SetPrevious(*currentNode);
				//	}
				//}
			}
		}

		//	Create path in reverse from endNode to startNode
		vector<Node*> path;
		Node* currentNode = endNode;

		while (currentNode != nullptr) {
			path.insert(path.begin(), currentNode);
			currentNode = currentNode->previous;
		}

		//	Return the path for navigation between startNode/endNode
		return path;
	}

	std::vector<Node*> AStarSearch(Node* startNode, Node* endNode)
	{
		//	Validate the input
		if (startNode == nullptr) {	//	If startNode is null OR endNode is NULL
			//	Raise error
			cout << "Search Validation Error: startNode is not valid." << endl;
			return vector<Node*>();
		}
		else if (endNode == nullptr) {
			cout << "Search Validation Error: endNode is not valid." << endl;
			return vector<Node*>();
		}

		if (&startNode == &endNode) {	//	If startNode == endNode
			//	Return empty path
			vector<Node*> emptyPath;
			//emptyPath.push_back(startNode);
			return emptyPath;
		}

		//	Initialise the starting node
		startNode->gScore = 0;
		startNode->previous = nullptr;

		//	Create our temporary lists for storing nodes we're visiting/visited
		vector<Node*> openList;
		vector<Node*> closedList;

		//	Add startNode to openList
		openList.push_back(startNode);

		//	While openList is not empty
		while (!openList.empty()) {
			//	Sort openList based on gScore
			sort(openList.begin(), openList.end(), ASort);

			Node* currentNode = *openList.begin();

			//	If we visit the endNode, we can conclude early
			//	This is a performance optimisation, and can miss more optimal paths
			if (currentNode == endNode) {
				break;
			}

			//	Remove currentNode from openList
			openList.erase(openList.begin());

			//	Add currentNode to closedList
			closedList.push_back(currentNode);

			//	For all connections c in currentNode
			for (Edge c : currentNode->m_connections) {
				//	If target is in closedList
				if (find(closedList.begin(), closedList.end(), c.target) != closedList.end()) {
					//	Don't process target, it has already been processed.
					continue;
				}

				//	Calculate the gScore for the target.
				float gScore = currentNode->gScore + c.cost;
				float hScore = AHeuristic(c.target, endNode, 'm');
				float fScore = gScore + hScore;

				//	If target is not in openList, process target.
				if (find(openList.begin(), openList.end(), c.target) == openList.end()) {
					//	This target has not been visited, so we must
					//update its gScore to the value we've calculated,
					//update its parent, and add it to the openList.
					c.target->gScore = gScore;
					c.target->fScore = fScore;
					c.target->SetPrevious(*currentNode);
					openList.push_back(c.target);
				}
				//	Target is already in the openList with a valid gScore.
				//	So compare the calculated gScore with the existing
				//to find the shorter path.
				else if (currentNode->gScore < c.target->gScore) {
					c.target->gScore = currentNode->gScore;
					c.target->fScore = currentNode->fScore;
					c.target->SetPrevious(*currentNode);
				}
			}
		}

		//	Create path in reverse from endNode to startNode
		vector<Node*> path;
		Node* currentNode = endNode;

		while (currentNode != nullptr) {
			path.insert(path.begin(), currentNode);
			currentNode = currentNode->previous;
		}

		//	Return the path for navigation between startNode/endNode
		return path;
	}

	Edge::Edge() : target(nullptr), cost(0) {}
	Edge::Edge(Node& _target, float _cost) : target(&_target), cost(_cost) {}
	Edge::~Edge() {}
	//Node& Edge::GetTarget() { return *target; }
	void Edge::SetTarget(Node& newTarget) { target = &newTarget; }

	Node::Node() : m_position(0, 0), gScore(0), previous(nullptr) {}
	Node::Node(float x, float y) : m_position(x, y), gScore(0), previous(nullptr) {}
	Node::~Node() {}
	void Node::ConnectTo(Node& other, float cost) { m_connections.push_back(Edge(other, cost)); }
	Node& Node::GetPrevious() { return *previous; }
	void Node::SetPrevious(Node& newPrevious) { previous = &newPrevious; }

	void NodeMap::Initialise(vector<string> asciiMap, int cellSize)
	{
		m_cellSize = cellSize;
		const char emptySquare = '0';

		//	assume all strings are the same length, so we'll size the map according
		//to the number of strings and the length of the first one

		m_height = asciiMap.size();
		m_width = asciiMap[0].size();

		m_nodes = new Node * [m_width * m_height];

		//	loop over the strings, creating Node entries as we go

		for (int y = 0; y < m_height; y++)
		{
			string& line = asciiMap[y];

			//	report to the user that you have a mis-matched string length

			if (line.size() != m_width)
			{
				cout << "Mismatched line #" << y << " in ASCII map (" << line.size() << " instead of " << m_width << ")" << endl;
			}

			for (int x = 0; x < m_width; x++)
			{
				//	get the xth character, or return an empty node if the string
				//isn't long enough

				char tile = x < line.size() ? line[x] : emptySquare;

				//	create a node for anything but a 'x' character

				m_nodes[x + m_width * y] = tile == emptySquare ? nullptr
					: new Node(((float)x + 0.5f) * m_cellSize, ((float)y + 0.5f) * m_cellSize);
			}
		}

		//	now loop over the nodes, creating connections between each node and its
		//neighbour to the West and South on the grid. This will link up all nodes

		for (int y = 0; y < m_height; y++)
		{
			for (int x = 0; x < m_width; x++)
			{
				Node* node = GetNode(x, y);

				if (node)
				{
					//	see if there's a node to our West, checking for array overruns
					//first if we're on the West-most edge

					Node* nodeWest = x == 0 ? nullptr : GetNode(x - 1, y);

					if (nodeWest)
					{
						node->ConnectTo(*nodeWest, 1);	//	TODO weights
						nodeWest->ConnectTo(*node, 1);
					}

					//	see if there's a node south of us, checking for array index
					//overruns again

					Node* nodeSouth = y == 0 ? nullptr : GetNode(x, y - 1);

					if (nodeSouth)
					{
						node->ConnectTo(*nodeSouth, 1);
						nodeSouth->ConnectTo(*node, 1);
					}
				}
			}
		}
	}

	Node* NodeMap::GetNode(int x, int y) { return m_nodes[x + m_width * y]; }

	void NodeMap::Draw()
	{
		Color cellColor;
		cellColor.a = 255;
		cellColor.r = 255;
		cellColor.g = 0;
		cellColor.b = 0;

		Color lineColor;
		lineColor.a = 255;
		lineColor.r = 0;
		lineColor.g = 0;
		lineColor.b = 0;

		for (int y = 0; y < m_height; y++)
		{
			for (int x = 0; x < m_width; x++)
			{
				Node* node = GetNode(x, y);
				if (node == nullptr)
				{
					//	draw a solid block in emptry squares without a navigation node

					DrawRectangle((x * m_cellSize), (y * m_cellSize),
						m_cellSize - 1, m_cellSize - 1, cellColor);
				}
				else
				{
					//	Draw the connections between the node and its neighbours
					for (int i = 0; i < node->m_connections.size(); i++)
					{
						Node* other = node->m_connections[i].target;
						DrawLine(node->m_position.x, node->m_position.y,
							other->m_position.x, other->m_position.y,
							lineColor);
					}
				}
			}
		}
	}

	Node* NodeMap::GetClosestNode(glm::vec2 worldPos)
	{
		int x = worldPos.x / m_cellSize;
		if (x < 0 || x >= m_width) { return nullptr; }

		int y = worldPos.y / m_cellSize;
		if (y < 0 || y >= m_height) { return nullptr; }

		return GetNode(x, y);
	}

	Node* NodeMap::GetRandomNode()
	{
		Node* node = nullptr;
		
		while (node == nullptr) {
			int x = rand() % m_width;
			int y = rand() % m_height;
			node = GetNode(x, y);

			//node = GetClosestNode(glm::vec2(x, y));
		}
		
		//std::cout << "Found valid random node at X: " << node->m_position.x << ". Y: " << node->m_position.y << std::endl;

		return node;
	}
}