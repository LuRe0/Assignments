#pragma once
#include "BehaviorNode.h"

class L_WanderingBehaviour : public BaseNode<L_WanderingBehaviour>
{
public:
    L_WanderingBehaviour();

protected:
    const float m_CircleRadius = 100;
    const float m_CircleOffset = 100.0f;
    const float m_WanderRange = 0.1f;
    const float m_WanderRadius = 25;
    //const float m_WanderOffset = 10;
    //float m_WanderOrientation = 0;

    float m_WanderAngle = M_PI_2;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};