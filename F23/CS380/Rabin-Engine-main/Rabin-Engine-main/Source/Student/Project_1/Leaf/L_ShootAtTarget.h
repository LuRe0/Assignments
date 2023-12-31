#pragma once
#include "BehaviorNode.h"

class L_ShootAtTarget : public BaseNode<L_ShootAtTarget>
{
public:
    L_ShootAtTarget();

protected:

    Agent* m_TargetAgent;

    float m_ShootingDelay;
    float m_ShootingTimer;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;

    bool ShootBullets();

};