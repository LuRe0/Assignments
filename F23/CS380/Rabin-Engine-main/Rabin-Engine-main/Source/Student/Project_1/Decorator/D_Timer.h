#pragma once
#include "BehaviorNode.h"

class D_Timer : public BaseNode<D_Timer>
{
public:
    D_Timer();

protected:
    float m_Timer;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};