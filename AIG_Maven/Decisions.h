#pragma once
#include "Decision.h"
//#include "Agent.h"
#include "Condition.h"

using namespace FSM;

namespace Trees
{
	class ABDecision : public Decision
	{
	private:
		Decision* m_a;
		Decision* m_b;
		Condition* m_condition;

	public:
		ABDecision() { m_a = nullptr; m_b = nullptr; m_condition = nullptr; }
		~ABDecision() { delete m_a; delete m_b; }
		
		virtual void MakeDecision(/*FSM::*/Agent* agent, float deltaTime) override;
	};
}