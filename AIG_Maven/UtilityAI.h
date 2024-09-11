#pragma once
#include "Behaviour.h"
#include <vector>

namespace FSM
{
	class UtilityAI : public Behaviour {
	private:
		std::vector<Behaviour*> m_behaviours;
		Behaviour* m_currentBehaviour;

	public:
		UtilityAI() {}
		~UtilityAI();

		virtual void Update(Agent* agent, float deltaTime) override;

		void AddBehaviour(Behaviour* _behaviour) { m_behaviours.push_back(_behaviour); }
	};
}