#pragma once

namespace FSM
{
	class Agent;

	class Behaviour	{
	public:
		virtual void Update(Agent* agent, float deltaTime) = 0;
		virtual void Enter(Agent* agent) {}
		virtual void Exit(Agent* agent) {}
	};
}