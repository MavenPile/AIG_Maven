#pragma once
#include "Agent.h"

//using namespace FSM;

namespace Trees
{		
	class Decision
	{
	public:
		virtual void MakeDecision(FSM::Agent* agent, float deltaTime) = 0;
	};
}