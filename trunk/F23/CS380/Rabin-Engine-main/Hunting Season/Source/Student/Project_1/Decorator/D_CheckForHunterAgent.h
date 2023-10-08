#pragma once
#include "BehaviorNode.h"

class D_CheckForHunterAgent : public BaseNode<D_CheckForHunterAgent>
{
public:
    D_CheckForHunterAgent();

protected:

    virtual void on_enter() override;
    virtual void on_update(float dt) override;

    bool m_IsAlive;
};