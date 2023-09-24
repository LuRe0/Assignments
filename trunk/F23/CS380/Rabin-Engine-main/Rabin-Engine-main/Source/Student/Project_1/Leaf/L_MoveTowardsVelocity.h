#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_MoveTowardsVelocity : public BaseNode<L_MoveTowardsVelocity>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    //Vec3 targetPoint;
};