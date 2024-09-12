#include "Decisions.h"
//#include "Condition.h"

namespace Trees
{
	void ABDecision::MakeDecision(FSM::Agent* agent, float deltaTime) {
		if (m_condition->IsTrue(agent)) {
			m_a->MakeDecision(agent, deltaTime);
		}
		else {
			m_b->MakeDecision(agent, deltaTime);
		}
	}
}