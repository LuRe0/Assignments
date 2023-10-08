#pragma once
#include "BehaviorNode.h"

class D_CheckForGuardAgents : public BaseNode<D_CheckForGuardAgents>
{
public:
    D_CheckForGuardAgents();

protected:

    virtual void on_enter() override;
    virtual void on_update(float dt) override;

    bool m_HasEnough;

    const int m_Max = 5;

    int m_Current;
};