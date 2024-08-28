#pragma once
#include <vector>
#include <string>

struct Node;

class NodeMap
{
	int m_width, m_height;
	float m_cellsize;

	Node** m_nodes;

public:
	void Initialise(std::vector<std::string> asciiMap, int cellSize);

	Node& GetNode(int x, int y) {
		return *m_nodes[x + m_width * y];
	}

	void Draw();
};