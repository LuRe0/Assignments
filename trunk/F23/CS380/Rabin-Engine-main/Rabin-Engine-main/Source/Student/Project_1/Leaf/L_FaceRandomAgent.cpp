#include <pch.h>
#include "L_FaceRandomAgent.h"

void L_FaceRandomAgent::on_enter()
{
    BehaviorNode::on_enter();

    // set animation, speed, etc

    // find the agent that is the furthest from this one
    float longestDistance = std::numeric_limits<float>().min();
    Vec3 furthestPoint;
    bool targetFound = false;

    // get a list of all current agents
    const auto &allAgents = agents->get_all_agents();


    if (!allAgents.empty())
    {
        m_TargetAgent = allAgents[RNG::range(0, (int)(allAgents.size() - 1))];
    }
    else // couldn't find a viable agent
    {
        on_failure();
    }
}

void L_FaceRandomAgent::on_update(float dt)
{
    bool result = false;

    const auto currentPos = agent->get_position();

    auto delta = m_TargetAgent->get_position() - currentPos;

    const float length = delta.Length();


	delta.Normalize();

	const float yaw = std::atan2(delta.x, delta.z);
	agent->set_yaw(yaw);

    on_success();
    
    display_leaf_text();
}

