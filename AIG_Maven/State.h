#pragma once
#include <vector>

namespace FSMDemo
{
	class State;
	class GameObject;
	class StateMachine;

	class Transition
	{
		

	public:
		virtual bool ConditionMet(GameObject* agent) = 0;
		State* m_target;
	};
	
	class State
	{

	
	public:
		virtual void Update(GameObject* agent, StateMachine* sm) = 0;
		virtual void Init(GameObject* agent) = 0;
		virtual void Exit(GameObject* agent) = 0;
		std::vector<Transition*> m_transitions;
	};
}