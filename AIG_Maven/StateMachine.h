#pragma once

namespace FSMDemo
{
	class GameObject;
	class State;

	class StateMachine
	{
		State* m_currentState;
		State* m_prevState;
		State* m_nextState;

	public:
		void Update(GameObject* agent);
		void RequestStateChange(State* newState);

		State* GetCurrentState();
		State* GetPrevState();
	};
}