#include <pch.h>
#include "L_FlockingBehaviour.h"

L_FlockingBehaviour::L_FlockingBehaviour() 
{}

Vec3 L_FlockingBehaviour::Separate(const std::vector<Agent*>& flockList, Vec3 curr_velocity)
{
	int total = 0;
	Vec3 steeringVelocity;
	//float distance = agent->get_blackboard().get_value<float>("MinimumRadius");

	for (const auto& a : flockList)
	{
		if (a != agent)
		{
			float d = Vec3::Distance(a->get_position(), agent->get_position());

			if (d < m_Distance)
			{
				BehaviorAgent* other = dynamic_cast<BehaviorAgent*>(a);

				Vec3 diff = agent->get_position() - other->get_position();

				diff /= d;

				steeringVelocity += diff;

				++total;
			}
		}
	}

	if (total > 0)
	{
		steeringVelocity /= (float)total;
		steeringVelocity -= curr_velocity;
	}

	steeringVelocity *= m_SCoefficient;

	return steeringVelocity;
}

Vec3 L_FlockingBehaviour::Allign(const std::vector<Agent*>& flockList, Vec3 curr_velocity)
{
	int total = 0;
	Vec3 steeringVelocity;
	float distance = agent->get_blackboard().get_value<float>("MinimumRadius");

	for (const auto& a : flockList)
	{
		if (a != agent)
		{
			float d = Vec3::Distance(a->get_position(), agent->get_position());

			if (d < distance)
			{
				BehaviorAgent* other = dynamic_cast<BehaviorAgent*>(a);

				steeringVelocity += other->get_blackboard().get_value<Vec3>("Velocity");

				++total;
			}
		}
	}

	if (total > 0)
	{
		steeringVelocity /= (float)total;
		steeringVelocity -= curr_velocity;
	}

	steeringVelocity *= m_ACoefficient;

	return steeringVelocity;

}

Vec3 L_FlockingBehaviour::Cohese(const std::vector<Agent*>& flockList, Vec3 curr_velocity)
{
	int total = 0;
	Vec3 steeringVelocity;
	float distance = agent->get_blackboard().get_value<float>("MinimumRadius");

	for (const auto& a : flockList)
	{
		if (a != agent)
		{
			float d = Vec3::Distance(a->get_position(), agent->get_position());

			if (d < distance)
			{
				BehaviorAgent* other = dynamic_cast<BehaviorAgent*>(a);

				steeringVelocity += other->get_position();

				++total;
			}
		}
	}

	if (total > 0)
	{
		steeringVelocity /= (float)total;
		steeringVelocity -= agent->get_position();
		steeringVelocity -= curr_velocity;
	}

	steeringVelocity *= m_CCoefficient;

	return steeringVelocity;
}

Vec3 L_FlockingBehaviour::ObjectAvoidance(Vec3 curr_velocity)
{
	int total = 0;
	Vec3 steeringVelocity;
	float distance = agent->get_blackboard().get_value<float>("MinimumRadius");
	const auto& guardList = agents->get_all_agents_by_type("Guards");

	for (const auto& a : guardList)
	{
		if (a != agent)
		{
			BehaviorAgent* other = dynamic_cast<BehaviorAgent*>(a);

			Vec3 otherVelocity = other->get_blackboard().get_value<Vec3>("Velocity");

			Vec3 nextAPos = other->get_position() + otherVelocity;
			Vec3 nextPos = agent->get_position() + agent->get_blackboard().get_value<Vec3>("Velocity");

			float d = Vec3::Distance(nextPos, nextAPos);

			if (d < distance)
			{
				steeringVelocity += (curr_velocity - otherVelocity);

				++total;
			}
		}
	}


	//if (total > 0)
	//{
	//	steeringVelocity /= (float)total;
	//}

	return steeringVelocity;
}

Vec3 L_FlockingBehaviour::Tether()
{
	Vec3 steeringVelocity;
	Vec3 pos = agent->get_position();
	if (pos.x < 0 || pos.z < 0 || pos.x > terrain->mapSizeInWorld || pos.z > terrain->mapSizeInWorld)
	{
		Vec3 tetherPoint = Vec3(terrain->mapSizeInWorld * 0.5f, 0, terrain->mapSizeInWorld * 0.5f);

		steeringVelocity = tetherPoint - pos;

		steeringVelocity.Normalize();

		steeringVelocity *= agent->get_movement_speed();
	}

	steeringVelocity *= m_TCoefficient;

	return steeringVelocity;
}

void L_FlockingBehaviour::on_enter()
{
	BehaviorNode::on_leaf_enter();


}

void L_FlockingBehaviour::on_update(float dt)
{
	Vec3  currentVelocity = agent->get_blackboard().get_value<Vec3>("Velocity");
	const auto& flockList = agents->get_all_agents_by_type(agent->get_type());

	Vec3 pos = agent->get_position();
	Vec3 steeringVelocity = currentVelocity;


	steeringVelocity += Separate(flockList, currentVelocity);
	steeringVelocity += Allign(flockList, currentVelocity);
	steeringVelocity += Cohese(flockList, currentVelocity);
	if (agent->get_type() == "Flocks")
	{
		steeringVelocity += ObjectAvoidance(currentVelocity);
	}
	steeringVelocity += Tether();

	steeringVelocity.Normalize();

	steeringVelocity *= agent->get_movement_speed();

	agent->get_blackboard().set_value("Velocity", steeringVelocity);

	//on_success();
	result = NodeResult::SUCCESS;

    display_leaf_text();
}

