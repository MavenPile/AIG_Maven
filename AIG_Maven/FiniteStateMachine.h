#pragma once
#include "Behaviour.h"
#include "Condition.h"
#include <vector>

namespace FSM
{
	class State	{
	public:
		struct Transition	{
			Condition* m_condition;	//	owned - must be handled
			State* m_targetState;	//	reference
		};

	private:
		std::vector<Behaviour*> m_behaviours;
		std::vector<Transition*> m_transitions;

	public:
		State() {}
		State(Behaviour* behaviour) { m_behaviours.push_back(behaviour); }
		~State();
		virtual void Update(Agent* agent, float deltaTime);
		virtual void Enter(Agent* agent);
		virtual void Exit(Agent* agent) {}

		std::vector<Transition*> GetTransitions() { return m_transitions; }
		void AddTransition(Condition* _condition, State* _targetState);
	};

	class FiniteStateMachine : Behaviour	{
	private:
		std::vector<State*> m_states;

		State* m_currentState;
		State* m_newState;

	public:
		FiniteStateMachine(State* s) : m_currentState(s), m_newState(nullptr) {}
		virtual ~FiniteStateMachine();

		virtual void Update(Agent* agent, float deltaTime) override;

		void AddState(State* state) { m_states.push_back(state); }

		virtual void Enter(Agent* agent) override;
	};
}