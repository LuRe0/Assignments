#pragma once
#include "BehaviorNode.h"

class L_SpawnFlocks : public BaseNode<L_SpawnFlocks>
{
public:
    L_SpawnFlocks();

protected:

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};