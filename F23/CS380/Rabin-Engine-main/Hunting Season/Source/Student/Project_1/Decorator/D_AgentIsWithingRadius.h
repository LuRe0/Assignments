#pragma once
#include "BehaviorNode.h"

class D_AgentIsWithingRadius : public BaseNode<D_AgentIsWithingRadius>
{
public:
    D_AgentIsWithingRadius();

protected:
    float m_Radius;
    char* m_Type;

    bool m_found;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};