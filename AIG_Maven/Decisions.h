#pragma once
#include "Decision.h"

using namespace FSM;

namespace Trees
{
	//	BRANCH
	
	class TrueFalseDecision : public Decision
	{
	private:
		Decision* m_true;	//	owned
		Decision* m_false;	//	owned
		Condition* m_condition;	//	owned

		Decision* m_lastDecision; // reference

	public:
		TrueFalseDecision() { m_true = nullptr; m_false = nullptr; m_condition = nullptr; m_lastDecision = nullptr; }
		~TrueFalseDecision() { delete m_true; delete m_false; delete m_condition; }
		
		void AddTrue(Decision* _true) { m_true = _true; }
		void AddFalse(Decision* _false) { m_false = _false; }
		virtual void AddCondition(Condition* _condition) override;

		virtual bool MakeDecision(Agent* agent, float deltaTime) override;

		Decision* GetLastDecision() { return m_lastDecision; }

		virtual void Exit(Agent* agent) override;
	};

	//	LEAF

	class BehaviourDecision : public Decision
	{
	private:
		Behaviour* m_behaviour;	//	owned

	public:
		BehaviourDecision() { m_behaviour = nullptr; }
		~BehaviourDecision() { delete m_behaviour; }

		virtual void AddBehaviour(Behaviour* _behaviour) override;

		virtual bool MakeDecision(Agent* agent, float deltaTime) override;

		virtual void Enter(Agent* agent) override;

		virtual void Exit(Agent* agent) override;
	};

	class AttackDecision : public Decision
	{
	private:
		int m_damage;
		float m_range;
		Condition* m_condition;

	public:
		AttackDecision(int _dmg, float _range) : m_damage(_dmg), m_range(_range), m_condition(nullptr) {}
		~AttackDecision() {}

		virtual void AddCondition(Condition* _condition) override;

		virtual bool MakeDecision(Agent* agent, float deltaTime) override;
	};
}