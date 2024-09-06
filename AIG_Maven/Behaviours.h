#pragma once
#include "Behaviour.h"

namespace Decision
{
	class WanderBehaviour : public Behaviour
	{
	public:
		virtual void Update(Agent* agent, float deltaTime) override;
	};

	class GoToPointBehaviour : public Behaviour
	{
	public:
		virtual void Update(Agent* agent, float deltaTime) override;
	};

	class FollowingBehaviour : public Behaviour
	{
	private:
		Vector2 m_lastTargetPosition;
	
	public:
		virtual void Update(Agent* agent, float deltaTime) override;
	};
}