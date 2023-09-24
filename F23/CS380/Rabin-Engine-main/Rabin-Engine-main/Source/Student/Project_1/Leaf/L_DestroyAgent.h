#pragma once
#include "BehaviorNode.h"

class L_DestroyAgent : public BaseNode<L_DestroyAgent>
{
public:
    L_DestroyAgent();

protected:
    float timer;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};