#include <pch.h>
#include "L_SpawnGuards.h"
#include "Projects/ProjectOne.h"

L_SpawnGuards::L_SpawnGuards()
{}

void L_SpawnGuards::on_enter()
{
	BehaviorNode::on_leaf_enter();

	//on_failure();
}

void L_SpawnGuards::on_update(float dt)
{

	int num = agent->get_blackboard().get_value<int>("MaxGuards");
	int count = 0;
	for (size_t i = 0; i < num; i++)
	{
		BehaviorAgent* guards = agents->create_behavior_agent("Guards", BehaviorTreeTypes::BT_Guard);

		if (guards)
		{
			char* etype = "Hunter";

			guards->get_blackboard().set_value("ChaseRadius", 100.0f);

			guards->get_blackboard().set_value("Velocity", Vec3(RNG::range(-agent->get_movement_speed(), agent->get_movement_speed()), 0, RNG::range(-agent->get_movement_speed(), agent->get_movement_speed())));

			guards->get_blackboard().set_value("Prey", etype);

			//guards->get_blackboard().set_value("CollisionTarget", type);

			guards->set_scaling(Vec3(0.7, 0.7, 0.7));
			guards->set_color(Vec3(1, 0, 0));
			guards->set_position(agent->get_position());

			++count;
		}
	}

	if (count == num)
	{
		on_success();
	}
	else
	{
		on_failure();
	}

    display_leaf_text();
}
