#pragma once
#include "BehaviorNode.h"

class L_SpawnHunterAgent : public BaseNode<L_SpawnHunterAgent>
{
public:
    L_SpawnHunterAgent();

protected:

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};