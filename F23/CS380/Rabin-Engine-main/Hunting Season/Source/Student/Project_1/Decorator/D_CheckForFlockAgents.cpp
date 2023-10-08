#include <pch.h>
#include "D_CheckForFlockAgents.h"

D_CheckForFlockAgents::D_CheckForFlockAgents()
{
}

void D_CheckForFlockAgents::on_enter()
{
    //delay = RNG::range(1.0f, 2.0f);

    BehaviorNode::on_enter();

    // get a list of all current agents
    const auto& allAgents = agents->get_all_agents_by_type("Flocks");

    // and our agent's position
    if (allAgents.size() < (m_Max / 2))
    {
        agent->get_blackboard().set_value("MaxFlocks", int(m_Max - allAgents.size()));

        m_HasEnough = false;
    }
    else // couldn't find a viable agent
    {
        on_failure();
    }


}

void D_CheckForFlockAgents::on_update(float dt)
{
    if (!m_HasEnough)
    {
        BehaviorNode* child = children.front();

        child->tick(dt);

        // assume same status as child
        set_status(child->get_status());
        set_result(child->get_result());

        m_HasEnough = true;
    }
    else
    {
        on_success();
    }


}
