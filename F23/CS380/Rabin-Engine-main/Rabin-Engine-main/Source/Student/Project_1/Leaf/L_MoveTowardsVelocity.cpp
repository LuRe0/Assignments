#include <pch.h>
#include "L_MoveTowardsVelocity.h"
#include "Agent/BehaviorAgent.h"

void L_MoveTowardsVelocity::on_enter()
{
    // set animation, speed, etc

    //targetPoint = RNG::world_position();
    //agent->look_at_point(targetPoint);

	BehaviorNode::on_leaf_enter();
}

void L_MoveTowardsVelocity::on_update(float dt)
{
    //const auto result = agent->move_toward_point(targetPoint, dt);


    auto delta = agent->get_blackboard().get_value<Vec3>("Velocity");

    const float length = delta.Length();

    // determine how far to actually move
    float actualSpeed = agent->get_movement_speed() * dt;

    delta.Normalize();
    delta *= actualSpeed;

    const auto nextPos = agent->get_position() + delta;
    agent->set_position(nextPos);

    const float yaw = std::atan2(delta.x, delta.z);
    agent->set_yaw(yaw);
    
    //if (result == true)
    //{
   
    //}
    result = NodeResult::SUCCESS;


    display_leaf_text();
}
