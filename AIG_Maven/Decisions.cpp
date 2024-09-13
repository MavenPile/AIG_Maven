#include "Decisions.h"
//#include "Condition.h"
#include "Behaviours.h"

namespace Trees
{
	void TrueFalseDecision::AddCondition(Condition* _condition)	{
		m_condition = _condition;
	}

	bool TrueFalseDecision::MakeDecision(FSM::Agent* agent, float deltaTime) {
		if (m_condition->IsTrue(agent)) {

			if (m_lastDecision != m_true) {
				//if (m_lastDecision) {
				//	m_lastDecision->Exit(agent);
				//}

				m_false->Exit(agent);
				m_true->Enter(agent);
				m_lastDecision = m_true;
			}

			return m_true->MakeDecision(agent, deltaTime);
		}
		else {

			//	If we're entering a new decision/behaviour
			if (m_lastDecision != m_false) {

				//	Exit the old decision
				if (m_lastDecision) {
					m_lastDecision->Exit(agent);
				}

				//	Enter the new decision
				m_false->Enter(agent);

				//	Cache the new decision
				m_lastDecision = m_false;
			}

			return m_false->MakeDecision(agent, deltaTime);
		}

		return false;
	}

	void TrueFalseDecision::Exit(Agent* agent)
	{
		m_lastDecision = nullptr;
	}

	void BehaviourDecision::AddBehaviour(Behaviour* _behaviour)	{
		m_behaviour = _behaviour;
	}

	bool BehaviourDecision::MakeDecision(FSM::Agent* agent, float deltaTime) {
		m_behaviour->Update(agent, deltaTime);

		return true;
	}

	void BehaviourDecision::Enter(Agent* agent)	{
		m_behaviour->Enter(agent);
	}

	void BehaviourDecision::Exit(Agent* agent)
	{
		m_behaviour->Exit(agent);
	}

	void AttackDecision::AddCondition(Condition* _condition)	{
		m_condition = _condition;
	}

	bool AttackDecision::MakeDecision(Agent* agent, float deltaTime)	{
		return false;
	}
}