#include <pch.h>
#include "C_SameFrame_Sequencer.h"

C_SameFrame_Sequencer::C_SameFrame_Sequencer() : currentIndex(0)
{}

void C_SameFrame_Sequencer::on_enter()
{
    currentIndex = 0;
    BehaviorNode::on_enter();
}

void C_SameFrame_Sequencer::on_update(float dt)
{
    // if any child fails, the node fails
    // if all children succeed, the node succeeds

    for (size_t i = 0; i < children.size(); i++)
    {
        BehaviorNode* currentNode = children[i];
        currentNode->tick(dt);

        if (currentNode->failed() == true)
        {
            on_failure();
            return;
        }
        else if (currentNode->succeeded() == true)
        {
            // move to the next node
            ++currentIndex;
        }
    }

    on_success();
}
