#include "Conditions.h"
#include "glm/glm.hpp"
#include "Agent.h"

namespace FSM
{
	bool DistanceCondition::IsTrue(Agent* agent) {
		if (agent->GetStoredTarget()) {
			return (glm::distance(agent->GetPosition(), agent->GetStoredTarget()->GetPosition()) < m_distance) == m_lessThan;
		}
		
		return false;
	}
}