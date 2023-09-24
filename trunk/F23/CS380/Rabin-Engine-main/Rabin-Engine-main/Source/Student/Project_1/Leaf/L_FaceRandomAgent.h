#pragma once
#include "BehaviorNode.h"
#include "Agent/BehaviorAgent.h"

class L_FaceRandomAgent : public BaseNode<L_FaceRandomAgent>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    Agent* m_TargetAgent;
};