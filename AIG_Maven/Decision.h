#pragma once
#include "Agent.h"
#include "Condition.h"
#include "Behaviour.h"

namespace Trees
{		
	class Decision
	{
	public:
		virtual bool MakeDecision(FSM::Agent* agent, float deltaTime) = 0;
		virtual void AddCondition(FSM::Condition* _condition) {}
		virtual void AddBehaviour(FSM::Behaviour* _behaviour) {}

		virtual void Enter(FSM::Agent* agent) {}
		virtual void Exit(FSM::Agent* agent) {}
	};
}