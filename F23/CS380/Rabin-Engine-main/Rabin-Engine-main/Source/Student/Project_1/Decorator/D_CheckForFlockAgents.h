#pragma once
#include "BehaviorNode.h"

class D_CheckForFlockAgents : public BaseNode<D_CheckForFlockAgents>
{
public:
    D_CheckForFlockAgents();

protected:

    virtual void on_enter() override;
    virtual void on_update(float dt) override;

    bool m_HasEnough;

    const int m_Max = 50;
};