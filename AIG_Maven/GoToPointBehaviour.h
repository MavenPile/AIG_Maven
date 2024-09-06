#pragma once
#include "Behaviour.h"

using namespace Decision;

class GoToPointBehaviour : public Behaviour
{
public:
	virtual void Update(Agent* agent, float deltaTime) override;
};

