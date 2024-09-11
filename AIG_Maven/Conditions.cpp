#include "Conditions.h"
#include "glm/glm.hpp"
#include "Agent.h"

namespace FSM
{
	bool DistanceCondition::IsTrue(Agent* agent) {
		return (glm::distance(agent->GetPosition(), agent->GetStoredTarget()->GetPosition()) < m_distance) == m_lessThan;
	}
}