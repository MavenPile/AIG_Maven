#pragma once
#include "Behaviour.h"
#include "glm/glm.hpp"
#include "Decision.h"

//using namespace Trees;

//class Decision;

namespace FSM
{
	class WanderBehaviour : public Behaviour
	{
		Color m_colour = { 0,255,0,255 };
	
	public:
		virtual void Update(Agent* agent, float deltaTime) override;
		virtual void Enter(Agent* agent) override;
		virtual float Evaluate(Agent* agent) override;

		//Color GetColour() { return m_colour; }
	};

	class GoToPointBehaviour : public Behaviour
	{
	public:
		virtual void Update(Agent* agent, float deltaTime) override;
	};

	class FollowingBehaviour : public Behaviour
	{
	private:
		glm::vec2 m_lastTargetPosition;
		Color m_colour = { 0,0,255,255 };
	
	public:
		virtual void Update(Agent* agent, float deltaTime) override;
		virtual void Enter(Agent* agent) override;
		virtual float Evaluate(Agent* agent) override;

		//Color GetColour() { return m_colour; }
	};

	class SelectorBehaviour : public Behaviour
	{
	private:
		Behaviour* m_b1;	//	owned by SelectorBehaviour
		Behaviour* m_b2;	//	owned by SelectorBehaviour
		Behaviour* m_selected;	//	a reference

	public:
		SelectorBehaviour(Behaviour* b1, Behaviour* b2) : m_b1(b1), m_b2(b2), m_selected(nullptr) {}
		~SelectorBehaviour() { delete m_b1; delete m_b2; }

		virtual void Update(Agent* agent, float deltaTime) override;
		void SetBehaviour(Behaviour* b, Agent* agent);
	};

	class DecisionBehaviour : public Behaviour
	{
	private:
		Trees::Decision* m_decision;

	public:
		//DecisionBehaviour() : m_decision(nullptr) {}
		DecisionBehaviour(Trees::Decision* _decision) : m_decision(_decision) {}
		~DecisionBehaviour() { delete m_decision; }

		virtual void Update(Agent* agent, float deltaTime) override;
	};

	class AttackBehaviour : public Behaviour
	{
	private:
		int m_dmg;
		float m_cooldown;
		Color m_colour = { 255,0,0,255 };

	public:
		AttackBehaviour(int _dmg, float _cooldown) : m_dmg(_dmg), m_cooldown(_cooldown) {}
		~AttackBehaviour() {}

		virtual void Update(Agent* agent, float deltaTime) override;
		virtual void Enter(Agent* agent) override;
		virtual float Evaluate(Agent* agent) override;

		//Color GetColour() { return m_colour; }
	};
}