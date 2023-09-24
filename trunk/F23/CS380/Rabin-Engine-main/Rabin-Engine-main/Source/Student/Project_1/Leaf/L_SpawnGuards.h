#pragma once
#include "BehaviorNode.h"

class L_SpawnGuards : public BaseNode<L_SpawnGuards>
{
public:
    L_SpawnGuards();

protected:

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};