#include <pch.h>
#include "L_FleeingBehaviour.h"

L_FleeingBehaviour::L_FleeingBehaviour() 
{}

void L_FleeingBehaviour::on_enter()
{
	BehaviorNode::on_leaf_enter();


}

void L_FleeingBehaviour::on_update(float dt)
{
	Vec3  currentVelocity = agent->get_blackboard().get_value<Vec3>("Velocity");
	const auto&  agressorList = agent->get_blackboard().get_value<std::vector<Agent*>>("TargetList");

	Vec3 pos = agent->get_position();
	Vec3 steeringVelocity;


	for (const auto& a : agressorList)
	{
		Vec3 desiredVelocity = pos - a->get_position();

		desiredVelocity.Normalize();

	

		desiredVelocity *= (agent->get_movement_speed());

		steeringVelocity = desiredVelocity - currentVelocity;

		currentVelocity += steeringVelocity;
	}

	agent->get_blackboard().set_value("Velocity", currentVelocity);

	//on_success();
	result = NodeResult::SUCCESS;

    display_leaf_text();
}
