#include "StateMachine.h"
#include "State.h"

namespace FSMDemo
{
	void StateMachine::Update(GameObject* agent) {
		for (Transition* t : m_currentState->m_transitions) {
			if (t->ConditionMet(agent)) {
				m_currentState->Exit(agent);
				t->m_target->Init(agent);
				m_prevState = m_currentState;
				m_currentState = t->m_target;
				break;
			}
		}

		m_currentState->Update(agent, this);
	}

	void StateMachine::RequestStateChange(State* newState) {
		m_nextState = newState;
	}

	State* StateMachine::GetCurrentState() {
		return m_currentState;
	}

	State* StateMachine::GetPrevState() {
		return m_prevState;
	}
}