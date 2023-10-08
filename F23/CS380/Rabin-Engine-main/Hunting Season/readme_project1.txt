Student Name: Anthon Reid

Project Name: Hunting Season

What I implemented: 
	In this project, I created a world with a flock, guards protecting the flock and a hunter trying to get to the flock.
I implemented the flock utilizes flocking behaviours to roam the map, and fleeing behaviour when the hunter is too close.
The guards use the pursuing behaviour to chase away the hunter otherwise they use the given move to random position node to patrol. 
The hunter himself can pursue, evade, wander and shoot at the flock when he is in range. There is an overseer who's sole purpuse is to spawn
more actors to keep the chase going.
	It is interesting how at times, the guards will randomly circle around the flock as though they are herding them. It was not an inteded behaviour.
The flock is aware of the guards, but the guards have no knowledge of the flock or each other. 

Directions (if needed):

What I liked about the project and framework:
	After spending months working in my GAM200 custom Engine, it was a bit odd to work in another with different rules.
For example the one control flow node I created was to emulate the control flow nodes in my own engine where all children of the control flow
nodes would be processed in a for loop. In this engine, it would process them one at a time. This cause me to rethink how I wanted to approach the project.
Essentially, I had to spend a lot of time just reading through the files and finding/learning cool new approaches. It was almost like looking at the next step
of things I had already done. For example the templated RNG file, or the Templated Map of variables in the blackboard, are techniques I will keep in mind for the future.

What I disliked about the project and framework:
	The most obvious but ultimately inconsequential thing was the the fact that this implementation of behaviour trees was fundamentally different that my own.
This cause me to constantly think, "I would have been done by now if this worked like mine". Unfortunately, this was the goal of the assignement. Aside from that, I found nothing
which I disliked.

Any difficulties I experienced while doing the project:
	It took me a while to realize that there is no true physics update in the framework. So implementing Steering behaviours was a bit hard.

Hours spent:

New selector node (name): 
	None

New Sequencer node (name): 
	C_SameFrame_Sequencer

New decorator nodes (names): 
	D_AgentIsWithingRadius
	D_CheckCollision
	D_CheckForFlockAgents
	D_CheckForGuardAgents
	D_CheckForHunterAgent
	D_Timer

10 total nodes (names):
	C_SameFrame_Sequencer

	D_AgentIsWithingRadius	
	D_CheckCollision
	D_CheckForFlockAgents
	D_CheckForGuardAgents
	D_CheckForHunterAgent
	D_Timer
	
	L_DestroyAgent
	L_DestroyAgentOnLeaveMap
	L_FaceRandomAgent
	L_FleeingBehaviour
	L_FlockingBehaviour
	L_PursuingBehaviour
	L_ShootAtTarget
	L_SpawnFlocks
	L_SpawnGuards
	L_SpawnHunterAgent
	L_WanderingBehaviour
	

4 Behavior trees (names):
	BT_Hunter
	BT_Guard
	BT_Overseer
	BT_Flocks
	BT_Bullet (Incomplete)

Extra credit:
	Steering Behaviours
		 Wandering : This one was extremely hard to figure out. Per your recommendation I did look at some youtube videos. The Coding Train had a fantastic one where they
				explained how it work and attemted to implement it themselves. My implementation is inpired by their approach. I do not think mine works as well but 
				the character moves interestingly.
Pursue, Evade and Tethering: Those where the easiest one to implement, it was simply, find the vector between self and target, and adjust velocity to either match it or
				move away from it.
		  Flocking : I had attempted to do flocking and Flowfield in GAM250 project in an attempt to create a swarm enemy, it mostly works. Two sources that were especially
				useful in helping me grasp the concept before and now were, The Coding Train's video and another by William Y. Feng. 
	  Object Avoidance : I tried to impelement this. In order to have the flocks avoid the guards, I see it happen at times, but I think that the other flocking forces override 					their attempts. 
						