#include <pch.h>
#include "Projects/ProjectTwo.h"
#include "P2_Pathfinding.h"
#include "SimpleMath.h"
#define _USE_MATH_DEFINES
#include <math.h>



const float m_SQRT2 = static_cast<float>(M_SQRT2);
const int m_MAPWIDTH = 40;
const int m_MAPHEIGHT = 40;



//#define Cost(e, s)   ((e.row == s.row || e.col == s.col) ? 1 : m_SQRT2)
//#define Octile_Ret(ret = std::minmax(std::fabsf(static_cast<float>(s.row - e.row)), std::fabs(static_cast<float>(s.col - e.col))); ret.first + m_SQRT2_1 * ret.second;))

#pragma region Extra Credit
bool ProjectTwo::implemented_floyd_warshall()
{
	return false;
}

bool ProjectTwo::implemented_goal_bounding()
{
	return false;
}

bool ProjectTwo::implemented_jps_plus()
{
	return false;
}
#pragma endregion

bool AStarPather::initialize()
{
	// handle any one-time setup requirements you have

	/*
		If you want to do any map-preprocessing, you'll need to listen
		for the map change message.  It'll look something like this:

		Callback cb = std::bind(&AStarPather::your_function_name, this);
		Messenger::listen_for_message(Messages::MAP_CHANGE, cb);

		There are other alternatives to using std::bind, so feel free to mix it up.
		Callback is just a typedef for std::function<void(void)>, so any std::invoke'able
		object that std::function can wrap will suffice.
	*/

	Callback cb = std::bind(&AStarPather::InitializeNewMap, this);


	Messenger::listen_for_message(Messages::MAP_CHANGE, cb);

	return true; // return false if any errors actually occur, to stop engine initialization
}

void AStarPather::shutdown()
{
	m_OpenList.Clear();

	for (size_t i = 0; i < m_NodeList.size(); i++)
	{
		delete m_NodeList[i];
	}

	m_NodeList.clear();
}

PathResult AStarPather::compute_path(PathRequest& request)
{
	/*
		This is where you handle pathing requests, each request has several fields:

		start/goal - start and goal world positions
		path - where you will build the path upon completion, path should be
			start to goal, not goal to start
		heuristic - which heuristic calculation to use
		weight - the heuristic weight to be applied
		newRequest - whether this is the first request for this path, should generally
			be true, unless single step is on

		smoothing - whether to apply smoothing to the path
		rubberBanding - whether to apply rubber banding
		singleStep - whether to perform only a single A* step
		debugColoring - whether to color the grid based on the A* state:
			closed list nodes - yellow
			open list nodes - blue

			use terrain->set_color(row, col, Colors::YourColor);
			also it can be helpful to temporarily use other colors for specific states
			when you are testing your algorithms

		method - which algorithm to use: A*, Floyd-Warshall, JPS+, or goal bounding,
			will be A* generally, unless you implement extra credit features

		The return values are:
			PROCESSING - a path hasn't been found yet, should only be returned in
				single step mode until a path is found
			COMPLETE - a path to the goal was found and has been built in request.path
			IMPOSSIBLE - a path from start to goal does not exist, do not add start position to path
	*/

	// WRITE YOUR CODE HERE


	if (request.newRequest) {
		//Initialize everything.Clear Open / Closed Lists.

		//    Push Start Node onto the Open List with cost of f(x) = g(x) + h(x).

		if (m_CurrentMap != terrain->get_map_index())
		{

			Messenger::send_message(Messages::MAP_CHANGE);

			return PathResult::PROCESSING;
		}
		else
		{
			m_OpenList.Clear();
		}

		m_RequestID += 1;

		m_CurrentHeuristic = m_Heuristics[static_cast<size_t>(request.settings.heuristic)];


		//m_PathSettings = m_PostProcessing[std::make_pair(request.settings.smoothing, request.settings.rubberBanding)];


		const GridPos start = terrain->get_grid_position(request.start);
		const GridPos goal = terrain->get_grid_position(request.goal);

		m_StartNode = GetNode(start.row, start.col);
		m_GoalNode = GetNode(goal.row, goal.col);

		m_StartNode->list = OpenList;
		m_StartNode->givenCost = 0;
		m_StartNode->finalCost = m_StartNode->givenCost + m_CurrentHeuristic(m_GoalNode->gridPos, m_StartNode->gridPos) * request.settings.weight;

		m_OpenList.Push(m_StartNode);
	}
	//While(Open List is not empty) {
	while (!m_OpenList.Empty())
	{
		//    parentNode = Pop cheapest node off Open List.
		Node* parentNode = m_OpenList.Pop();

		if (!parentNode)
			continue;

		if (parentNode->list!= OpenList)
			continue;

		//If parentNode is the Goal Node, then path found(return PathResult::COMPLETE).
		if (parentNode == m_GoalNode)
		{

			if (request.settings.rubberBanding && request.settings.smoothing)
			{
				std::vector<Vec3> list;
				RubberSmoothing(m_GoalNode, list);
				request.path = std::list(list.begin(), list.end());
				return PathResult::COMPLETE;
			}
			else if (request.settings.rubberBanding)
			{
				std::vector<Vec3> list;
				RubberBanding(m_GoalNode, list);
				request.path = std::list(list.begin(), list.end());
				return PathResult::COMPLETE;
			}
			else if (request.settings.smoothing)
			{
				std::vector<Vec3> list;
				Smoothing(m_GoalNode, list);
				request.path = std::list(list.begin(), list.end());
				return PathResult::COMPLETE;
			}

			Node* pathHead = m_GoalNode;
			//add path to list 
			while (pathHead)
			{
				request.path.push_front(terrain->get_world_position(pathHead->gridPos));

				pathHead = pathHead->parent;
			}

			//request.path.push_front(terrain->get_world_position(pathHead->gridPos));

			return PathResult::COMPLETE;
		}

		//Place parentNode on the Closed List.
		parentNode->list = ClosedList;


		int* dir;

		int row;
		int col;

		Node* neighbor;

		float givenCost;

		//float heuristicCost;

		float finalCost;

		float old_cost;
		//const float cost = (i % 2 == 0) ? 1 : m_SQRT2;


		//const float givenCost = parentNode->givenCost + (i % 2 == 0) ? 1 : m_SQRT2;
		
		////LOOP UNROLLING FOR THE WIN

		if (parentNode->mNeighbors & (1 << 0))
		{
			dir = m_Dirs[0];

			row = parentNode->gridPos.row + dir[0];
			col = parentNode->gridPos.col + dir[1];

			neighbor = GetNode(row, col);

			//const float cost = (i % 2 == 0) ? 1 : m_SQRT2;


			givenCost = parentNode->givenCost + 1;

			//givenCost = parentNode->givenCost + Cost(parentNode->gridPos, neighbor->gridPos);

			//Compute its cost, f(x) = g(x) + h(x)

			//If child node isn’t on Open or Closed list, put it on Open List.
			// or if child node is on Open or Closed List,
			if (neighbor->list == NoList || givenCost < neighbor->givenCost)
			{
				//AND this new one is cheaper,
				if (neighbor->list == NoList)
					neighbor->heuristicCost = m_CurrentHeuristic(m_GoalNode->gridPos, neighbor->gridPos);

				finalCost = givenCost + neighbor->heuristicCost * request.settings.weight;

				//then take the old expensive one off both lists and put this new
				//cheaper one on the Open List.
				old_cost = neighbor->finalCost;

				neighbor->givenCost = givenCost;
				neighbor->parent = parentNode;
				neighbor->finalCost = finalCost;

				if (neighbor->list != OpenList)
				{
					neighbor->list = OpenList;
					m_OpenList.Push(neighbor);
				}
				else
				{
					m_OpenList.Update(neighbor, old_cost);
					//m_OpenList.Update();
				}
			}
		}

		if (parentNode->mNeighbors & (1 << 1))
		{
			dir = m_Dirs[1];

			row = parentNode->gridPos.row + dir[0];
			col = parentNode->gridPos.col + dir[1];

			neighbor = GetNode(row, col);

			//const float cost = (i % 2 == 0) ? 1 : m_SQRT2;


			//const float givenCost = parentNode->givenCost + (i % 2 == 0) ? 1 : m_SQRT2;

			givenCost = parentNode->givenCost + m_SQRT2;

			//Compute its cost, f(x) = g(x) + h(x)

			//If child node isn’t on Open or Closed list, put it on Open List.
			// or if child node is on Open or Closed List,
			if (neighbor->list == NoList || givenCost < neighbor->givenCost)
			{
				//AND this new one is cheaper,
				if (neighbor->list == NoList)
					neighbor->heuristicCost = m_CurrentHeuristic(m_GoalNode->gridPos, neighbor->gridPos);

				finalCost = givenCost + neighbor->heuristicCost * request.settings.weight;

				//then take the old expensive one off both lists and put this new
				//cheaper one on the Open List.
				old_cost = neighbor->finalCost;

				neighbor->givenCost = givenCost;
				neighbor->parent = parentNode;
				neighbor->finalCost = finalCost;

				if (neighbor->list != OpenList)
				{
					neighbor->list = OpenList;
					m_OpenList.Push(neighbor);
				}
				else
				{
					m_OpenList.Update(neighbor, old_cost);
					//m_OpenList.Update();
				}
			}
		}

		if (parentNode->mNeighbors & (1 << 2))
		{
			dir = m_Dirs[2];

			row = parentNode->gridPos.row + dir[0];
			col = parentNode->gridPos.col + dir[1];

			neighbor = GetNode(row, col);

			//const float cost = (i % 2 == 0) ? 1 : m_SQRT2;


			//const float givenCost = parentNode->givenCost + (i % 2 == 0) ? 1 : m_SQRT2;

			givenCost = parentNode->givenCost + 1;

			//Compute its cost, f(x) = g(x) + h(x)

			//If child node isn’t on Open or Closed list, put it on Open List.
			// or if child node is on Open or Closed List,
			if (neighbor->list == NoList || givenCost < neighbor->givenCost)
			{
				//AND this new one is cheaper,
				if (neighbor->list == NoList)
					neighbor->heuristicCost = m_CurrentHeuristic(m_GoalNode->gridPos, neighbor->gridPos);

				finalCost = givenCost + neighbor->heuristicCost * request.settings.weight;

				//then take the old expensive one off both lists and put this new
				//cheaper one on the Open List.
				old_cost = neighbor->finalCost;

				neighbor->givenCost = givenCost;
				neighbor->parent = parentNode;
				neighbor->finalCost = finalCost;

				if (neighbor->list != OpenList)
				{
					neighbor->list = OpenList;
					m_OpenList.Push(neighbor);
				}
				else
				{
					m_OpenList.Update(neighbor, old_cost);
					//m_OpenList.Update();
				}
			}
		}

		if (parentNode->mNeighbors & (1 << 3))
		{
			dir = m_Dirs[3];

			row = parentNode->gridPos.row + dir[0];
			col = parentNode->gridPos.col + dir[1];

			neighbor = GetNode(row, col);

			//const float cost = (i % 2 == 0) ? 1 : m_SQRT2;


			//const float givenCost = parentNode->givenCost + (i % 2 == 0) ? 1 : m_SQRT2;

			givenCost = parentNode->givenCost + m_SQRT2;

			//Compute its cost, f(x) = g(x) + h(x)

			//If child node isn’t on Open or Closed list, put it on Open List.
			// or if child node is on Open or Closed List,
			if (neighbor->list == NoList || givenCost < neighbor->givenCost)
			{
				//AND this new one is cheaper,
				if (neighbor->list == NoList)
					neighbor->heuristicCost = m_CurrentHeuristic(m_GoalNode->gridPos, neighbor->gridPos);

				finalCost = givenCost + neighbor->heuristicCost * request.settings.weight;

				//then take the old expensive one off both lists and put this new
				//cheaper one on the Open List.
				old_cost = neighbor->finalCost;

				neighbor->givenCost = givenCost;
				neighbor->parent = parentNode;
				neighbor->finalCost = finalCost;

				if (neighbor->list != OpenList)
				{
					neighbor->list = OpenList;
					m_OpenList.Push(neighbor);
				}
				else
				{
					m_OpenList.Update(neighbor, old_cost);
					//m_OpenList.Update();
				}
			}
		}

		if (parentNode->mNeighbors & (1 << 4))
		{
			dir = m_Dirs[4];

			row = parentNode->gridPos.row + dir[0];
			col = parentNode->gridPos.col + dir[1];

			neighbor = GetNode(row, col);

			//const float cost = (i % 2 == 0) ? 1 : m_SQRT2;


			//const float givenCost = parentNode->givenCost + (i % 2 == 0) ? 1 : m_SQRT2;

			givenCost = parentNode->givenCost + 1;

			//Compute its cost, f(x) = g(x) + h(x)

			//If child node isn’t on Open or Closed list, put it on Open List.
			// or if child node is on Open or Closed List,
			if (neighbor->list == NoList || givenCost < neighbor->givenCost)
			{
				//AND this new one is cheaper,
				if (neighbor->list == NoList)
					neighbor->heuristicCost = m_CurrentHeuristic(m_GoalNode->gridPos, neighbor->gridPos);

				finalCost = givenCost + neighbor->heuristicCost * request.settings.weight;

				//then take the old expensive one off both lists and put this new
				//cheaper one on the Open List.
				old_cost = neighbor->finalCost;

				neighbor->givenCost = givenCost;
				neighbor->parent = parentNode;
				neighbor->finalCost = finalCost;

				if (neighbor->list != OpenList)
				{
					neighbor->list = OpenList;
					m_OpenList.Push(neighbor);
				}
				else
				{
					m_OpenList.Update(neighbor, old_cost);
					//m_OpenList.Update();
				}
			}
		}

		if (parentNode->mNeighbors & (1 << 5))
		{
			dir = m_Dirs[5];

			row = parentNode->gridPos.row + dir[0];
			col = parentNode->gridPos.col + dir[1];

			neighbor = GetNode(row, col);

			//const float cost = (i % 2 == 0) ? 1 : m_SQRT2;


			//const float givenCost = parentNode->givenCost + (i % 2 == 0) ? 1 : m_SQRT2;

			givenCost = parentNode->givenCost + m_SQRT2;

			//Compute its cost, f(x) = g(x) + h(x)

			//If child node isn’t on Open or Closed list, put it on Open List.
			// or if child node is on Open or Closed List,
			if (neighbor->list == NoList || givenCost < neighbor->givenCost)
			{
				//AND this new one is cheaper,
				if (neighbor->list == NoList)
					neighbor->heuristicCost = m_CurrentHeuristic(m_GoalNode->gridPos, neighbor->gridPos);

				finalCost = givenCost + neighbor->heuristicCost * request.settings.weight;

				//then take the old expensive one off both lists and put this new
				//cheaper one on the Open List.
				old_cost = neighbor->finalCost;

				neighbor->givenCost = givenCost;
				neighbor->parent = parentNode;
				neighbor->finalCost = finalCost;

				if (neighbor->list != OpenList)
				{
					neighbor->list = OpenList;
					m_OpenList.Push(neighbor);
				}
				else
				{
					m_OpenList.Update(neighbor, old_cost);
					//m_OpenList.Update();
				}
			}
		}

		if (parentNode->mNeighbors & (1 << 6))
		{
			dir = m_Dirs[6];

			row = parentNode->gridPos.row + dir[0];
			col = parentNode->gridPos.col + dir[1];

			neighbor = GetNode(row, col);

			//const float cost = (i % 2 == 0) ? 1 : m_SQRT2;


			//const float givenCost = parentNode->givenCost + (i % 2 == 0) ? 1 : m_SQRT2;

			givenCost = parentNode->givenCost + 1;

			//Compute its cost, f(x) = g(x) + h(x)

			//If child node isn’t on Open or Closed list, put it on Open List.
			// or if child node is on Open or Closed List,
			if (neighbor->list == NoList || givenCost < neighbor->givenCost)
			{
				//AND this new one is cheaper,

				if (neighbor->list == NoList)
					neighbor->heuristicCost = m_CurrentHeuristic(m_GoalNode->gridPos, neighbor->gridPos);

				finalCost = givenCost + neighbor->heuristicCost * request.settings.weight;

				//then take the old expensive one off both lists and put this new
				//cheaper one on the Open List.
				old_cost = neighbor->finalCost;

				neighbor->givenCost = givenCost;
				neighbor->parent = parentNode;
				neighbor->finalCost = finalCost;

				if (neighbor->list != OpenList)
				{
					neighbor->list = OpenList;
					m_OpenList.Push(neighbor);
				}
				else
				{
					m_OpenList.Update(neighbor, old_cost);
					//m_OpenList.Update();
				}
			}
		}

		if (parentNode->mNeighbors & (1 << 7))
		{
			dir = m_Dirs[7];

			row = parentNode->gridPos.row + dir[0];
			col = parentNode->gridPos.col + dir[1];

			neighbor = GetNode(row, col);

			//const float cost = (i % 2 == 0) ? 1 : m_SQRT2;

			
			//const float givenCost = parentNode->givenCost + (i % 2 == 0) ? 1 : m_SQRT2;

			givenCost = parentNode->givenCost + m_SQRT2;

			//Compute its cost, f(x) = g(x) + h(x)

			//If child node isn’t on Open or Closed list, put it on Open List.
			// or if child node is on Open or Closed List,
			if (neighbor->list == NoList || givenCost < neighbor->givenCost)
			{
				//AND this new one is cheaper,
				if (neighbor->list == NoList)
					neighbor->heuristicCost = m_CurrentHeuristic(m_GoalNode->gridPos, neighbor->gridPos);

				finalCost = givenCost + neighbor->heuristicCost * request.settings.weight;

				//then take the old expensive one off both lists and put this new
				//cheaper one on the Open List.
				old_cost = neighbor->finalCost;

				neighbor->givenCost = givenCost;
				neighbor->parent = parentNode;
				neighbor->finalCost = finalCost;

				if (neighbor->list != OpenList)
				{
					neighbor->list = OpenList;
					m_OpenList.Push(neighbor);
				}
				else
				{
					m_OpenList.Update(neighbor, old_cost);
					//m_OpenList.Update();
				}
			}
		}
		//m_OpenList.Update();
		//If taken too much time this frame(or if request.settings.singleStep == true),
		//abort search for now and resume next frame(return PathResult::PROCESSING).
		if (request.settings.singleStep)
		{

			if (request.settings.debugColoring)
			{
				for (int i = 0; i < m_MapWidth; i++)
				{
					for (int j = 0; j < m_MapHeight; j++)
					{
						Node* node = GetNode(i, j);

						if (node->list == OpenList)
						{
							terrain->set_color(node->gridPos, Colors::Blue);
						}
						else if (node->list == ClosedList)
						{
							terrain->set_color(node->gridPos, Colors::Yellow);
						}
						else
						{
							terrain->set_color(node->gridPos, Colors::White);
						}
					}
				}
			}

			return PathResult::PROCESSING;
		}
	}

	//if (m_OpenList.HasOptions())
	//{
	//	return PathResult::PROCESSING;

	//}

	//Open List empty, thus no path possible(return PathResult::IMPOSSIBLE).

	return PathResult::IMPOSSIBLE;
}


void AStarPather::InitializeNewMap()
{


	if (m_NodeList.empty())
	{
		AllocateMap();

		m_TileSize = (terrain->mapSizeInWorld / m_MapWidth);

		return;
	}

	m_MapWidth = terrain.get()->get_map_width();
	m_MapHeight = terrain.get()->get_map_height();

	m_TileSize = (terrain->mapSizeInWorld / m_MapWidth);


	m_OpenList.Clear();

	PrecomputeNeighbors();

	m_CurrentMap = terrain->get_map_index();
}

void AStarPather::PrecomputeNeighbors()
{
	for (int i = 0; i < m_MapWidth; i++)
	{
		for (int j = 0; j < m_MapHeight; j++)
		{
			Node* node = GetNode(i, j);

			node->mNeighbors = byte();

			for (size_t i = 0; i < Directions; i++)
			{
				const int* dir = m_Dirs.at((Direction)i);


				int row = node->gridPos.row + dir[0];
				int col = node->gridPos.col + dir[1];

				if (terrain->is_valid_grid_position(row, col))
				{
					const Node* neighbor = GetNode(row, col);

					if (neighbor)
					{
						if (!terrain->is_wall(neighbor->gridPos))
						{
							if (dir[0] != 0 && dir[1] != 0)
							{
								const Node* newAdj = GetNode(node->gridPos.row + dir[0], node->gridPos.col);
								const Node* newAdj2 = GetNode(node->gridPos.row, node->gridPos.col + dir[1]);
								if (newAdj && newAdj2)
								{
									if (!terrain->is_wall(newAdj->gridPos) && !terrain->is_wall(newAdj2->gridPos))
									{
										node->mNeighbors |= 1 << i;
									}
								}

							}
							else
							{
								node->mNeighbors |= 1 << i;
							}
						}
					}
				}
			}
		}
	}
}

//void AStarPather::ResetNodeData()
//{
//    for (int i = 0; i < m_MapWidth; i++)
//    {
//        for (int j = 0; j < m_MapHeight; j++)
//        {
//            m_NodeList[i * m_MAPWIDTH + j]->Reset();
//        }
//    }
//}

void AStarPather::NotPostProcessing(Node* pHead, std::vector<Vec3>& list)
{
	Node* pathHead = pHead;
	//add path to list 
	while (pathHead)
	{
		list.insert(list.begin(), terrain->get_world_position(pathHead->gridPos));

		pathHead = pathHead->parent;
	}
}

void AStarPather::RubberBanding(Node* pHead, std::vector<Vec3>& list)
{
	Node* curr = pHead;
	bool done = false;


	while (curr->parent)
	{

		Node* next;
		if (!curr->parent->parent)
		{
			next = curr->parent;
		}
		else
			next = curr->parent->parent;

		std::pair<int, int> range_r = std::minmax(curr->gridPos.row, next->gridPos.row);
		std::pair<int, int> range_c = std::minmax(curr->gridPos.col, next->gridPos.col);

		bool possible = true;
		for (int i = range_r.first; i <= range_r.second; i++)
		{
			if (!possible)
			{
				break;
			}
			for (int j = range_c.first; j <= range_c.second; j++)
			{
				GridPos newPos;
				newPos.row = i;
				newPos.col = j;

				if (terrain->is_wall(newPos))
				{
					possible = false;
					break;
				}
			}
		}
		if (possible)
		{
			if (next->parent)
				curr->parent = next;
			else
			{
				curr->parent = next;
				break;
			}
		}
		else
		{
			curr = curr->parent;
		}
	}



	Node* pathHead = pHead;
	//add path to list 
	while (pathHead)
	{
		list.insert(list.begin(), terrain->get_world_position(pathHead->gridPos));

		pathHead = pathHead->parent;
	}

}

void AStarPather::Smoothing(Node* pHead, std::vector<Vec3>& list)
{
	if (list.empty())
	{
		Node* pathHead = pHead;
		//add path to list 
		while (pathHead)
		{
			list.insert(list.begin(), terrain->get_world_position(pathHead->gridPos));

			pathHead = pathHead->parent;
		}
	}

	if (list.size() == 1)
	{
		return;
	}
	if (list.size() == 2)
	{
		int offset = 1;
		int index = 0;
		Vec3 p1 = Vec3::CatmullRom(list[index], list[index], list[index + offset], list[index + offset], 0.25f);
		list.insert(list.begin() + offset, p1);
		++offset;
		Vec3 p2 = Vec3::CatmullRom(list[index], list[index], list[index + offset], list[index + offset], 0.5f);
		list.insert(list.begin() + offset, p2);
		++offset;
		Vec3 p3 = Vec3::CatmullRom(list[index], list[index], list[index + offset], list[index + offset], 0.75f);
		list.insert(list.begin() + offset, p3);
		++offset;

		return;
	}

	int offset = 1;
	int index = 0;
	Vec3 p1 = Vec3::CatmullRom(list[index], list[index], list[index +offset], list[index+offset + 1], 0.25f);
	list.insert(list.begin() + offset, p1);
	++offset;
	Vec3 p2 = Vec3::CatmullRom(list[index], list[index], list[index + offset], list[index + offset + 1], 0.5f);
	list.insert(list.begin() + offset, p2);
	++offset;
	Vec3 p3 = Vec3::CatmullRom(list[index], list[index], list[index + offset], list[index + offset + 1], 0.75f);
	list.insert(list.begin() + offset, p3);



	Smoothing_Rec(list, index, offset, 3);


}

void AStarPather::RubberSmoothing(Node* pHead, std::vector<Vec3>& list)
{
	RubberBanding(pHead, list);


	RubberSmoothing_Rec(list, 0);


	Smoothing(pHead, list);

}

void AStarPather::RubberSmoothing_Rec(std::vector<Vec3>& list, int index)
{
	if (index + 1 == list.size())
	{
		return;
	}

	Vec3 p0 = list[index];
	Vec3 p1 = list[index+1];


	float distance = Vec3::Distance(p1, p0);

	float d = 1.5f * m_TileSize;

	if (distance > d)
	{
		Vec3 midpoint = (p1 - p0);

		midpoint *= 0.5f;

		midpoint = p0 + midpoint;

		list.insert(list.begin() + index + 1, midpoint);

		RubberSmoothing_Rec(list, index);
	}
	else
	{
		RubberSmoothing_Rec(list, index+1);
	}

}

void AStarPather::Smoothing_Rec(std::vector<Vec3>& list, int index, int offset, int depth)
{

	if (list.size() - depth == 3)
	{
		++offset;
		Vec3 p1 = Vec3::CatmullRom(list[index], list[index+ offset], list[index + offset + 1], list[index + offset + 1], 0.25f);
		list.insert(list.begin() + index + offset + 1, p1);
		++offset;
		Vec3 p2 = Vec3::CatmullRom(list[index], list[index + offset-1], list[index + offset + 1], list[index + offset + 1] , 0.5f);
		list.insert(list.begin() + index + offset + 1, p2);
		++offset;
		Vec3 p3 = Vec3::CatmullRom(list[index], list[index + offset-2], list[index + offset + 1], list[index + offset + 1], 0.75f);
		list.insert(list.begin() + index + offset + 1, p3);
		++offset;
		return;
	}

	++offset;
	Vec3 p1 = Vec3::CatmullRom(list[index], list[index + offset], list[index + offset + 1 ], list[index + offset + 2], 0.25f);
	list.insert(list.begin() + index + offset + 1, p1);
	++offset;
	Vec3 p2 = Vec3::CatmullRom(list[index], list[index + offset -1], list[index + offset + 1], list[index + offset + 2], 0.5f);
	list.insert(list.begin() + index + offset + 1, p2);
	++offset;
	Vec3 p3 = Vec3::CatmullRom(list[index], list[index + offset - 2], list[index + offset + 1], list[index + offset + 2], 0.75f);
	list.insert(list.begin() + index + offset + 1, p3);

	depth += 4;

	Smoothing_Rec(list, index + 4, 3, depth);

	//return  std::list(list.begin(), list.end());
}



float AStarPather::Octile(const GridPos& e, const GridPos& s)
{
	//const std::pair<int, int> ret = std::minmax(std::abs(s.row - e.row), std::abs(s.col - e.col));

	//eliminating std::abs is faster overall??????????? crazy
	const std::pair<int, int> r = std::minmax(s.col, e.col);
	const std::pair<int, int> c = std::minmax(s.row, e.row);
	const std::pair<int, int> ret = std::minmax(r.second - r.first, c.second - c.first);


	return (ret.first * m_SQRT2) + ret.second - ret.first;
}

float AStarPather::Manhattan(const GridPos& e, const GridPos& s)
{
	const float dx = static_cast<float>(s.row - e.row);
	const float dy = static_cast<float>(s.col - e.col);

	return std::fabs(dx) + std::fabs(dy);
}

float AStarPather::Chebyshev(const GridPos& e, const GridPos& s)
{
	const float dx = static_cast<float>(s.row - e.row);
	const float dy = static_cast<float>(s.col - e.col);

	return std::fmaxf(std::fabs(dx), std::fabs(dy));
}

float AStarPather::Euclidean(const GridPos& e, const GridPos& s)
{
	const float dx = static_cast<float>(s.row - e.row);
	const float dy = static_cast<float>(s.col - e.col);

	return std::sqrtf(std::fabs(dx * dx) + std::fabs(dy * dy));
}

float AStarPather::Inconsistent(const GridPos& e, const GridPos& s)
{
	if ((e.row + e.col) % 2 > 0)
	{
		return Euclidean(e, s);
	}

	return 0;
}

float AStarPather::Cost(const GridPos& e, const GridPos& s)
{
	//if (e.row == s.row || e.col == s.col)
	//{
	//    return 1;
	//}
	//else
	//{
	//    return (m_SQRT2);
	//}

	return (e.row == s.row || e.col == s.col) ? 1 : m_SQRT2;
}


void AStarPather::AllocateMap()
{
	m_MapWidth = terrain.get()->get_map_width();
	m_MapHeight = terrain.get()->get_map_height();

	int size = (m_MAPWIDTH * m_MAPHEIGHT);

	m_NodeList = std::vector<Node*>(size, nullptr);


	//m_TileSize = 400 / terrain->mapSizeInWorld;

	m_CurrentMap = terrain->get_map_index();

	for (int i = 0; i < m_MAPWIDTH; i++)
	{
		for (int j = 0; j < m_MAPHEIGHT; j++)
		{
			Node* node = new Node();

			node->gridPos.row = i;
			node->gridPos.col = j;

			m_NodeList[i * m_MAPWIDTH + j] = node;
		}
	}


	PrecomputeNeighbors();
}


AStarPather::Node* AStarPather::GetNode(const int row, const int col)
{
	Node* node = m_NodeList[row * m_MAPWIDTH + col];


	if (node->m_RequestID == m_RequestID) 
		return node;
	

	node->Reset();
	node->m_RequestID = m_RequestID;


	return node;
}

void AStarPather::Queued_List::Push(Node* node)
{
	m_List.push_back(node);

	static NodeSorter nodeSorter;
	std::push_heap(m_List.begin(), m_List.begin(), nodeSorter);
}

AStarPather::Node* AStarPather::Queued_List::Pop()
{
	//make heap everytime we pop to but min in front

	std::pop_heap(m_List.begin(), m_List.end(), NodeSorter()); // moves the smallest to the end

	Node* node = m_List.back();

	m_List.pop_back();

	return node;
}

void AStarPather::Queued_List::Update()
{
	std::make_heap(m_List.begin(), m_List.end(), NodeSorter()); // moves the smallest to the end
}

void AStarPather::Queued_List::Clear()
{
	m_List.clear();
}

inline void AStarPather::Queued_List::Remove(Node* node)
{
	auto itr = std::find(m_List.begin(), m_List.end(), node);

	if (itr != m_List.end())
	{
		const int index = static_cast<int>(itr - m_List.begin());
		std::swap(m_List[index], m_List.back());

		m_List.pop_back();
	}
}

bool AStarPather::Queued_List::Empty() const
{
	return m_List.empty();
}


AStarPather::Buckets::Buckets()
{
	m_MaxBucket = static_cast<int>(m_Buckets.size() - 1);
	m_CurrentLowestBucket = m_MaxBucket;
	m_CurrentBucket.reserve(1600);
}

void AStarPather::Buckets::Maintain()
{
	m_Buckets[m_CurrentLowestBucket].Update();
}


void AStarPather::Buckets::Push(Node* node)
{
	const int bucket = std::min(static_cast<int>(node->finalCost * m_Range), m_MaxBucket);
	m_CurrentLowestBucket = std::min(bucket, m_CurrentLowestBucket);

	m_Buckets[bucket].Push(node);
	m_CurrentBucket.push_back(bucket);
}

AStarPather::Node* AStarPather::Buckets::Pop()
{
	return m_Buckets[m_CurrentLowestBucket].Pop();
}

void AStarPather::Buckets::Update(Node* new_node, const float old_final_cost)
{
	///update this new node
	int bucket = std::min(static_cast<int>(new_node->finalCost * m_Range), m_MaxBucket);
	int old_bucket = std::min(static_cast<int>(old_final_cost * m_Range), m_MaxBucket);

	//if node belongs in other bucket
	if (old_bucket != bucket)
	{
		Remove(new_node, old_bucket);
		Maintain();
		Push(new_node);
	}
	else
	{
		m_Buckets[bucket].Update();
	}

}

void AStarPather::Buckets::Clear()
{
	if (m_CurrentBucket.empty())
	{
		return;
	}
	for (int bucket: m_CurrentBucket)
	{
		m_Buckets[bucket].Clear();
	}
	m_CurrentBucket.clear();
	//m_BucketHistory.reset();
}

inline void AStarPather::Buckets::Remove(Node* new_node, const int old_bucket)
{
	if (m_Buckets[old_bucket].Empty())
		return;

	m_Buckets[old_bucket].Remove(new_node);
}

bool AStarPather::Buckets::Empty()
{
	if (!m_Buckets[m_CurrentLowestBucket].Empty()) 
	{
		return false; 
	}

	size_t size = m_Buckets.size();
	for (int i = m_CurrentLowestBucket + 1; i < size; ++i) 
	{
		if (!m_Buckets[i].Empty()) 
		{
			m_CurrentLowestBucket = i;
			return false;
		}
	}

	return true;
}

