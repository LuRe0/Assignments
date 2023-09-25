#pragma once
#include "BehaviorNode.h"

class L_DestroyAgentOnLeaveMap : public BaseNode<L_DestroyAgentOnLeaveMap>
{
public:
    L_DestroyAgentOnLeaveMap();

protected:
    bool m_Destroy;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};