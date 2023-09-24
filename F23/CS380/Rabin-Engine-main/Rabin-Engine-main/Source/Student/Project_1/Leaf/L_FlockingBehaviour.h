#pragma once
#include "BehaviorNode.h"

class L_FlockingBehaviour : public BaseNode<L_FlockingBehaviour>
{
public:
    L_FlockingBehaviour();

protected:
    const float m_SCoefficient = 0.25f;
    const float m_ACoefficient = 0.5f;
    const float m_CCoefficient = 0.1f;
    const float m_TCoefficient = 0.3f;
    const float m_Distance = 5;

    Vec3 Separate(const std::vector<Agent*>& flockList, Vec3 curr_velocity);
    Vec3 Allign(const std::vector<Agent*>& flockList, Vec3 curr_velocity);
    Vec3 Cohese(const std::vector<Agent*>& flockList, Vec3 curr_velocity);
    Vec3 Tether();


    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};