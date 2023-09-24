#pragma once
#include "BehaviorNode.h"

class L_FleeingBehaviour : public BaseNode<L_FleeingBehaviour>
{
public:
    L_FleeingBehaviour();

protected:
    const float m_MaxForce = 15.0f;
    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};