#include "FiniteStateMachine.h"
#include <iostream>

namespace FSM
{
	State::~State()
	{
		//	The state owns the behaviours assigned to it
		//	The behaviours need to have their data unallocated when the FSM is destroyed
		for (Behaviour* b : m_behaviours)
		{
			delete b;
		}

		//	The transition owns the conditions assigned to it,
		//but the target states are references
		for (Transition* t : m_transitions)
		{
			delete t->m_condition;
		}

		//	The vectors handle their own memory
	}

	void State::Update(Agent* agent, float deltaTime)	{
		for (Behaviour* b : m_behaviours)	{
			b->Update(agent, deltaTime);
		}
	}

	void State::Enter(Agent* agent)	{
		for (Behaviour* b : m_behaviours)	{
			b->Enter(agent);
		}
	}

	void State::AddTransition(Condition* _condition, State* _targetState)	{
		Transition* newTransition = new Transition();
		newTransition->m_condition = _condition;
		newTransition->m_targetState = _targetState;

		m_transitions.push_back(newTransition);
	}

	FiniteStateMachine::~FiniteStateMachine()
	{
		//	The FSM owns every state assigned to it
		for (State* s : m_states)
		{
			delete s;
		}
	}

	void FiniteStateMachine::Update(Agent* agent, float deltaTime)
	{
		State* newState = nullptr;

		//	Check the current state's transitions
		for (State::Transition* t : m_currentState->GetTransitions()) {
			if (t->m_condition->IsTrue(agent)) {
				newState = t->m_targetState;
			}
		}

		//	If we've changed state, clean up the old one and initialise the new one
		if (newState != nullptr && newState != m_currentState) {
			m_currentState->Exit(agent);
			m_currentState = newState;
			m_currentState->Enter(agent);
		}
		
		//	Update the current state
		m_currentState->Update(agent, deltaTime);


	}

	void FiniteStateMachine::Enter(Agent* agent)
	{
		std::cout << "Entering State..." << std::endl;
		
		m_currentState->Enter(agent);
	}
}