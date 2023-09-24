#include <pch.h>
#include "L_DestroyAgent.h"

L_DestroyAgent::L_DestroyAgent() : timer(0.0f)
{}

void L_DestroyAgent::on_enter()
{
	BehaviorNode::on_leaf_enter();
}

void L_DestroyAgent::on_update(float dt)
{
    agents->destroy_agent(agent);

    on_success();

    display_leaf_text();
}
