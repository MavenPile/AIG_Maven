#pragma once
#include "BasePathAgent.h"
#include "Color.hpp"
#include "Pathfinding.h"

using namespace Pathfinding;

namespace Decision
{
	class Behaviour;
	
	class Agent
	{
		BasePathAgent m_pathAgent;
		Behaviour* m_current;
		NodeMap* m_nodeMap;
		Color m_colour;

	public:
		Agent() : m_current(nullptr), m_nodeMap(nullptr), m_colour({ 255,255,0,255 }) {}
		Agent(NodeMap* _nodeMap, Behaviour* _behaviour) : m_current(_behaviour), m_nodeMap(_nodeMap), m_colour({ 255,255,0,255 }) {}
		~Agent() { delete m_current; }

		void Update(float deltaTime);
		void Draw();
		void GoTo(glm::vec2 point);
		void SetNode(Node* node);
		BasePathAgent* GetBaseAgent();
	};
}