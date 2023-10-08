#include <pch.h>
#include "D_Timer.h"

D_Timer::D_Timer() : m_Timer(0.0f)
{}

void D_Timer::on_enter()
{
    m_Timer = RNG::range(1.0f, 5.0f);

    BehaviorNode::on_enter();
}

void D_Timer::on_update(float dt)
{
    m_Timer -= dt;

    if (m_Timer > 0.0f)
    {
        BehaviorNode *child = children.front();

        child->tick(dt);


        if (child->failed())
        {
            on_failure();
        }
    }
    else
    {
        on_success();
    }

}
