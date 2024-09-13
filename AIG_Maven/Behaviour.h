#pragma once
#include "Color.hpp"

namespace FSM
{
	class Agent;

	class Behaviour	{
	private:
		Color m_colour;
	
	public:
		virtual void Update(Agent* agent, float deltaTime) = 0;
		virtual void Enter(Agent* agent) {}
		virtual void Exit(Agent* agent) {}

		//	Used by UtilityAI to determine which behaviour to do
		virtual float Evaluate(Agent* agent) { return 0.f; }

		//	Colours
		virtual Color GetColour() { return m_colour; }
		virtual void SetColour(Color _colour) { m_colour = _colour; }
	};
}