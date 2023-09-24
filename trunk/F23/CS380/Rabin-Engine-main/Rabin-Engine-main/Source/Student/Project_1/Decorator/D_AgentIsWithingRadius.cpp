#include <pch.h>
#include "D_AgentIsWithingRadius.h"

D_AgentIsWithingRadius::D_AgentIsWithingRadius() : m_Radius(0.0f), m_found(false)
{}

void D_AgentIsWithingRadius::on_enter()
{
    BehaviorNode::on_enter();


    m_Radius = agent->get_blackboard().get_value<float>("MinimumRadius");
    m_Type = agent->get_blackboard().get_value<char*>("TargetType");

    const auto& allAgents = agents->get_all_agents_by_type(m_Type);

    const auto& currPos = agent->get_position();
    std::vector<Agent*> targetList;
    for (const auto& a : allAgents)
    {
        const auto& agentPos = a->get_position();
        const float distance = Vec3::Distance(currPos, agentPos);

        //if the agents are close enough
        if (distance <= m_Radius)
        {
            targetList.push_back(a);
            m_found = true;
        }
    }

    if (!targetList.empty())
    {
        agent->get_blackboard().set_value("TargetList", targetList);
    }

}

void D_AgentIsWithingRadius::on_update(float dt)
{
    if (m_found)
    {
        BehaviorNode* child = children.front();

        child->tick(dt);

        // assume same status as child
        result = NodeResult::SUCCESS;

        m_found = false;
    }
    else
    {
        on_failure();
    }

    display_leaf_text();

}
