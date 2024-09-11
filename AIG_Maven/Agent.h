#pragma once
#include "BasePathAgent.h"
#include "Color.hpp"
#include "Pathfinding.h"

using namespace Pathfinding;

namespace FSM
{
	class Behaviour;
	
	class Agent
	{
		BasePathAgent m_pathAgent;
		Behaviour* m_current;
		NodeMap* m_nodeMap;
		Color m_colour;
		Agent* m_targetAgent = nullptr;

	public:
		Agent() : m_current(nullptr), m_nodeMap(nullptr), m_colour({ 255,255,0,255 }) {}
		Agent(NodeMap* _nodeMap, Behaviour* _behaviour);
		~Agent() { delete m_current; }

		void Update(float deltaTime);
		void Draw();
		void GoTo(glm::vec2 point);

		void SetNode(Node* node);
		BasePathAgent* GetBaseAgent();

		bool PathComplete();

		NodeMap* GetMap();

		Agent* GetStoredTarget() { return m_targetAgent; }
		void SetStoredTarget(Agent* target) { m_targetAgent = target; }

		glm::vec2 GetPosition() { return m_pathAgent.m_position; }

		void Reset() { m_pathAgent.m_path.clear(); }
		void SetColour(Color colour) { m_colour = colour; }

		void SetSpeed(float speed) { m_pathAgent.SetSpeed(speed); }
	};
}