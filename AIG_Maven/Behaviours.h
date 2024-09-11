#pragma once
#include "Behaviour.h"
#include "glm/glm.hpp"

namespace FSM
{
	class WanderBehaviour : public Behaviour
	{
	public:
		virtual void Update(Agent* agent, float deltaTime) override;
		virtual void Enter(Agent* agent) override;
		virtual float Evaluate(Agent* agent) override;
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
	
	public:
		virtual void Update(Agent* agent, float deltaTime) override;
		virtual void Enter(Agent* agent) override;
		virtual float Evaluate(Agent* agent) override;
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
}