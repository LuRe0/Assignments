#include <pch.h>
#include "D_CheckForGuardAgents.h"

D_CheckForGuardAgents::D_CheckForGuardAgents() : m_HasEnough(false)
{}

void D_CheckForGuardAgents::on_enter()
{
    BehaviorNode::on_enter();

    // get a list of all current agents
    const auto& allAgents = agents->get_all_agents_by_type("Guards");

    // and our agent's position
    if (allAgents.empty())
    {
        agent->get_blackboard().set_value("MaxGuards", RNG::range(1, 10));
        m_HasEnough = false;
    }
    else // couldn't find a viable agent
    {
        on_failure();
    }

}

void D_CheckForGuardAgents::on_update(float dt)
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
