#include <pch.h>
#include "L_SpawnHunterAgent.h"
#include "Projects/ProjectOne.h"

L_SpawnHunterAgent::L_SpawnHunterAgent()
{}

void L_SpawnHunterAgent::on_enter()
{
	BehaviorNode::on_leaf_enter();
}

void L_SpawnHunterAgent::on_update(float dt)
{
    BehaviorAgent* hunter = agents->create_behavior_agent("Hunter", BehaviorTreeTypes::BT_Hunter);
	if (hunter)
	{
		char* type = "Guards";
		char* etype = "Flocks";

		hunter->get_blackboard().set_value("CollisionTarget", type);



		hunter->get_blackboard().set_value("MinimumRadius", 15.0f);
		hunter->get_blackboard().set_value("ShootingRadius", 25.0f);
		hunter->get_blackboard().set_value("ChaseRadius", 30.0f);

		hunter->get_blackboard().set_value("TargetType", type);
		hunter->get_blackboard().set_value("Prey", etype);


		hunter->set_movement_speed(7);

		hunter->set_scaling(Vec3(0.5,0.5,0.5));
		//hunter->set_color(Vec3(0.5,0.5,0.5));
		hunter->get_blackboard().set_value("Velocity", Vec3(RNG::range(-agent->get_movement_speed(), agent->get_movement_speed()), 0, RNG::range(-agent->get_movement_speed(), agent->get_movement_speed())));

		float x = RNG::range(0.0f, terrain->mapSizeInWorld);
		float z = RNG::range(0.0f, terrain->mapSizeInWorld);

		hunter->set_position(Vec3(x, 0, z));
		on_success();
	}

    display_leaf_text();
}
