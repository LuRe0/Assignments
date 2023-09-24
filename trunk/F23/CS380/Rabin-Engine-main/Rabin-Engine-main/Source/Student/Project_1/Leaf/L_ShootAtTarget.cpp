#include <pch.h>
#include "L_ShootAtTarget.h"
#include "Projects/ProjectOne.h"

L_ShootAtTarget::L_ShootAtTarget() : m_TargetAgent(nullptr)
{}

void L_ShootAtTarget::on_enter()
{
    // set animation, speed, etc

    // find the agent that is the furthest from this one
    float shortestDistance = agent->get_blackboard().get_value<float>("ShootingRadius");;
    Agent* target;
    bool targetFound = false;

    char* type = agent->get_blackboard().get_value<char*>("Prey");

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

            if (distance < shortestDistance)
            {
                shortestDistance = distance;
                target = a;
                targetFound = true;
                break;
            }
        }
    }

    if (targetFound == true)
    {
        m_TargetAgent = target;
        BehaviorNode::on_leaf_enter();
    }
    else // couldn't find a viable agent
    {
        on_failure();
    }


}

void L_ShootAtTarget::on_update(float dt)
{
    const auto result = ShootBullets();

    if (result == true)
    {
        on_success();
    }
    else
    {
        on_failure();
    }

    display_leaf_text();
}

bool L_ShootAtTarget::ShootBullets()
{

    //BehaviorAgent* bullet = agents->create_behavior_agent("Bullet", BehaviorTreeTypes::BT_Bullet);

    //if (bullet)
    //{


    //    Vec3 dir = m_TargetAgent->get_position() - agent->get_position();

    //    dir.Normalize();

    //    bullet->get_blackboard().set_value("Velocity", dir);
    //    char* type = "Flocks";
    //    bullet->get_blackboard().set_value("CollisionTarget", type);

    //    bullet->set_scaling(Vec3(0.5, 0.1, 0.5));
    //    bullet->set_color(Vec3(0, 1, 0));

    //    return true;
    //}
    return false;
}
