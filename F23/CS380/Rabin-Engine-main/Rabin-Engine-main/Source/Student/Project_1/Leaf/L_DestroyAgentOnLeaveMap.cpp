#include <pch.h>
#include "L_DestroyAgentOnLeaveMap.h"

L_DestroyAgentOnLeaveMap::L_DestroyAgentOnLeaveMap() : m_Destroy(false)
{}

void L_DestroyAgentOnLeaveMap::on_enter()
{
	BehaviorNode::on_leaf_enter();

	Vec3 pos = agent->get_position();
	if (pos.x < (0 - (terrain->mapSizeInWorld / 4.0f)) ||
		pos.z < (0 - (terrain->mapSizeInWorld / 4.0f)) ||
		pos.x > (terrain->mapSizeInWorld + (terrain->mapSizeInWorld / 4.0f)) ||
		pos.z >(terrain->mapSizeInWorld + (terrain->mapSizeInWorld / 4.0f)))
	{
		m_Destroy = true;
	}

}

void L_DestroyAgentOnLeaveMap::on_update(float dt)
{
	if (m_Destroy)
	{
		agents->destroy_agent(agent);

	}


	on_success();

    display_leaf_text();
}
