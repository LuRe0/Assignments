#pragma once
#include "BehaviorNode.h"

class L_PursuingBehaviour : public BaseNode<L_PursuingBehaviour>
{
public:
    L_PursuingBehaviour();

protected:
    Agent* m_TargetAgent;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};