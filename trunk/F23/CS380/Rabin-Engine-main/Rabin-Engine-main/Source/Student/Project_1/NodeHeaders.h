#pragma once

// Include all node headers in this file

// Example Control Flow Nodes
#include "ControlFlow/C_ParallelSequencer.h"
#include "ControlFlow/C_RandomSelector.h"
#include "ControlFlow/C_Selector.h"
#include "ControlFlow/C_Sequencer.h"

// Student Control Flow Nodes
#include "ControlFlow/C_SameFrame_Sequencer.h"



// Example Decorator Nodes
#include "Decorator/D_Delay.h"
#include "Decorator/D_InvertedRepeater.h"
#include "Decorator/D_RepeatFourTimes.h"



// Student Decorator Nodes
#include "Decorator/D_CheckCollision.h"
#include "Decorator/D_Timer.h"
#include "Decorator/D_CheckForHunterAgent.h"
#include "Decorator/D_CheckForGuardAgents.h"
#include "Decorator/D_CheckForFlockAgents.h"
#include "Decorator/D_AgentIsWithingRadius.h"


// Example Leaf Nodes
#include "Leaf/L_CheckMouseClick.h"
#include "Leaf/L_Idle.h"
#include "Leaf/L_MoveToFurthestAgent.h"
#include "Leaf/L_MoveToMouseClick.h"
#include "Leaf/L_MoveToRandomPosition.h"
#include "Leaf/L_PlaySound.h"
#include "Leaf/L_MoveToFurthestAgent.h"


// Student Leaf Nodes
#include "Leaf/L_ShootAtTarget.h"
#include "Leaf/L_MoveTowardsVelocity.h"
#include "Leaf/L_DestroyAgent.h"
#include "Leaf/L_FaceRandomAgent.h"
#include "Leaf/L_SpawnHunterAgent.h"
#include "Leaf/L_SpawnGuards.h"
#include "Leaf/L_SpawnFlocks.h"
#include "Leaf/L_FleeingBehaviour.h"
#include "Leaf/L_WanderingBehaviour.h"
#include "Leaf/L_FlockingBehaviour.h"