#include <pch.h>
#include "L_SpawnFlocks.h"
#include "Projects/ProjectOne.h"

L_SpawnFlocks::L_SpawnFlocks()
{}

void L_SpawnFlocks::on_enter()
{
	BehaviorNode::on_leaf_enter();

	//on_failure();
}

void L_SpawnFlocks::on_update(float dt)
{

	int num = agent->get_blackboard().get_value<int>("MaxFlocks");
	int count = 0;
	for (size_t i = 0; i < num; i++)
	{
		BehaviorAgent* flock = agents->create_behavior_agent("Flocks", BehaviorTreeTypes::BT_Flocks);

		if (flock)
		{
			char* type = "Bullet";
			char* eType = "Hunter";
			flock->get_blackboard().set_value("CollisionTarget", type);
			flock->get_blackboard().set_value("MinimumRadius", 7.0f);
			flock->get_blackboard().set_value("TargetType", eType);

			flock->set_movement_speed(10);

			flock->get_blackboard().set_value("Velocity", Vec3(RNG::range(-agent->get_movement_speed(), agent->get_movement_speed()), 0, RNG::range(-agent->get_movement_speed(), agent->get_movement_speed())));

			flock->set_scaling(Vec3(0.3, 0.3, 0.3));
			flock->set_color(Vec3(0, 0, 0));

			float x = RNG::range(0.0f, terrain->mapSizeInWorld);
			float z = RNG::range(0.0f, terrain->mapSizeInWorld);
			flock->set_position(Vec3(x, 0, z));

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
