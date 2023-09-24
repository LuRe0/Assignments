#include <pch.h>
#include "L_WanderingBehaviour.h"

L_WanderingBehaviour::L_WanderingBehaviour() 
{}

void L_WanderingBehaviour::on_enter()
{
	BehaviorNode::on_leaf_enter();


}

void L_WanderingBehaviour::on_update(float dt)
{
	Vec3  currentVelocity = agent->get_blackboard().get_value<Vec3>("Velocity");

	Vec3 pos = agent->get_position();
	Vec3 steeringVelocity;

	Vec3 orientation = currentVelocity;
	orientation.Normalize();

	Vec3 posOffset = currentVelocity;

	posOffset.Normalize();

	posOffset *= m_CircleOffset;

	posOffset += pos;

	float desiredAngle = m_WanderAngle + agent->get_yaw();

	float x = m_WanderRadius * std::cosf(desiredAngle);
	float y = m_WanderRadius * std::sinf(desiredAngle);

	Vec3 wanderPoint(x, 0, y);

	posOffset += wanderPoint;

	steeringVelocity = posOffset - pos;
	steeringVelocity += currentVelocity;
	steeringVelocity.Normalize();

	steeringVelocity *= agent->get_movement_speed();

	m_WanderAngle += RNG::range(-m_WanderRange, m_WanderRange);
	
	//m_WanderOrientation = RNG::range(-m_WanderRange, m_WanderRange);

	//float desiredOrientation = m_WanderOrientation + agent->get_yaw();

	//Vec3 targetPos = pos + (m_WanderOffset * orientation);

	//targetPos += m_WanderRadius * orientation;

	//steeringVelocity = targetPos - pos;

	//steeringVelocity.Normalize();

	//steeringVelocity *= agent->get_movement_speed();

	agent->get_blackboard().set_value("Velocity", steeringVelocity);

	//on_success();
	result = NodeResult::SUCCESS;

    display_leaf_text();
}
