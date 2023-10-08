#pragma once
#include "BehaviorNode.h"

class D_CheckCollision : public BaseNode<D_CheckCollision>
{
public:
    D_CheckCollision();

protected:

    virtual void on_enter() override;
    virtual void on_update(float dt) override;

    bool m_HasCollided;

    const float m_Dist = 5.0f;
};