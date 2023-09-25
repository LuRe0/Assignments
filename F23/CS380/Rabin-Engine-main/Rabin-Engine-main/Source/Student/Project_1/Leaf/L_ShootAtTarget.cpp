#include <pch.h>
#include "L_ShootAtTarget.h"
#include "Projects/ProjectOne.h"

L_ShootAtTarget::L_ShootAtTarget() : m_TargetAgent(nullptr), m_ShootingDelay(1.0f)
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
    if (m_ShootingTimer > 0)
    {
        m_ShootingTimer -= dt;

        return;
    }
    const auto result = ShootBullets();


    if (result == true)
    {
        on_success();

        m_ShootingTimer = m_ShootingDelay;
    }
    else
    {
        on_failure();
    }

    display_leaf_text();
}

bool L_ShootAtTarget::ShootBullets()
{

    BehaviorAgent* bullet = agents->create_behavior_agent("Bullet", BehaviorTreeTypes::BT_Bullet);

    if (bullet)
    {
        bullet->set_movement_speed(20);

        Vec3 dir = m_TargetAgent->get_position() - agent->get_position();


        dir.Normalize();

        const float yaw = std::atan2(dir.x, dir.z);
        agent->set_yaw(yaw);

        dir.Normalize();

        dir.y = 0;

        dir *= bullet->get_movement_speed();

        bullet->get_blackboard().set_value("Velocity", dir);
        char* type = "Flocks";
        bullet->get_blackboard().set_value("CollisionTarget", type);

        bullet->set_scaling(Vec3(0.2, 0.1, 0.2));
        bullet->set_color(Vec3(0, 1, 0));
        bullet->set_position(Vec3(agent->get_position().x, 1, agent->get_position().z));

        return true;
    }
    return false;
}
