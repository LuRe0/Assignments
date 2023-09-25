#include <pch.h>
#include "L_PursuingBehaviour.h"

L_PursuingBehaviour::L_PursuingBehaviour() 
{}

void L_PursuingBehaviour::on_enter()
{
	BehaviorNode::on_leaf_enter();

    float shortestDistance = agent->get_blackboard().get_value<float>("ChaseRadius");;
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

void L_PursuingBehaviour::on_update(float dt)
{
	Vec3  currentVelocity = agent->get_blackboard().get_value<Vec3>("Velocity");
	Vec3  targetAgentVelocity = dynamic_cast<BehaviorAgent*>(m_TargetAgent)->get_blackboard().get_value<Vec3>("Velocity");


	Vec3 pos = agent->get_position();
	Vec3 steeringVelocity;

    Vec3 desiredVelocity = (m_TargetAgent->get_position() + targetAgentVelocity) - pos;

    desiredVelocity.Normalize();

    desiredVelocity.y = 0;


    //steeringVelocity = desiredVelocity - currentVelocity;

    currentVelocity += desiredVelocity;

    currentVelocity.Normalize();

    currentVelocity *= (agent->get_movement_speed() * RNG::range(2.0f, 2.5f));

	agent->get_blackboard().set_value("Velocity", currentVelocity);

	//on_success();
	result = NodeResult::SUCCESS;

    display_leaf_text();
}
