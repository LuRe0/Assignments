#include <pch.h>
#include "D_CheckForHunterAgent.h"

D_CheckForHunterAgent::D_CheckForHunterAgent() : m_IsAlive(false)
{}

void D_CheckForHunterAgent::on_enter()
{
    BehaviorNode::on_enter();

    // get a list of all current agents
    const auto& allAgents = agents->get_all_agents_by_type("Hunter");

    // and our agent's position
    if (allAgents.empty())
    {
        m_IsAlive = false;
    }
    else
    {
        on_failure();
    }


}

void D_CheckForHunterAgent::on_update(float dt)
{
    if (!m_IsAlive)
    {
        BehaviorNode* child = children.front();

        child->tick(dt);

        // assume same status as child
        set_status(child->get_status());
        set_result(child->get_result());

        m_IsAlive = true;
    }
    else
    {
        on_success();
    }
}
