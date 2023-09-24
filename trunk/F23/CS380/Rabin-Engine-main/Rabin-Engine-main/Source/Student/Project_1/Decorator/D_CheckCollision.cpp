#include <pch.h>
#include "D_CheckCollision.h"

D_CheckCollision::D_CheckCollision() : m_HasCollided(false)
{}

void D_CheckCollision::on_enter()
{
    //delay = RNG::range(1.0f, 2.0f);

    char* type = agent->get_blackboard().get_value<char*>("CollisionTarget");

    // get a list of all current agents
    const auto& allAgents = agents->get_all_agents_by_type(type);

    // and our agent's position
    const auto& currPos = agent->get_position();

    for (const auto& a : allAgents)
    {
        // make sure it's not our agent
        if (a != agent)
        {
            const auto& agentPos = a->get_position();
            const float distance = Vec3::Distance(currPos, agentPos);

            //if the agents are close enough
            if (distance <= m_Dist)
            {
                m_HasCollided = true;

                break;
            }
        }
    }


    BehaviorNode::on_enter();
}

void D_CheckCollision::on_update(float dt)
{
    if (m_HasCollided)
    {
        BehaviorNode* child = children.front();

        child->tick(dt);

        // assume same status as child
        set_status(child->get_status());
        set_result(child->get_result());
    }
    else
    {
        on_success();
    }


    display_leaf_text();

}
