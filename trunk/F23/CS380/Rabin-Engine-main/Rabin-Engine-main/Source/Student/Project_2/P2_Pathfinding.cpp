#include <pch.h>
#include "Projects/ProjectTwo.h"
#include "P2_Pathfinding.h"
#define _USE_MATH_DEFINES
#include <math.h>


const float m_SQRT2 = static_cast<float>(M_SQRT2);
const float m_SQRT2_1 = (m_SQRT2 - 1.0f);
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

    //m_Heuristics.emplace(Heuristic::OCTILE, &AStarPather::Octile);
    //m_Heuristics.emplace(Heuristic::CHEBYSHEV, AStarPather::Chebyshev);
    //m_Heuristics.emplace(Heuristic::MANHATTAN, AStarPather::Manhattan);
    //m_Heuristics.emplace(Heuristic::EUCLIDEAN, AStarPather::Euclidean);
    //m_Heuristics.emplace(Heuristic::INCONSISTENT, AStarPather::Inconsistent);

    //m_Dirs.emplace(N,  std::make_pair<int, int>(1,0));
    //m_Dirs.emplace(NE, std::make_pair<int, int>(1,1));
    //m_Dirs.emplace(E,  std::make_pair<int, int>(0,1));
    //m_Dirs.emplace(SE, std::make_pair<int, int>(-1,1));
    //m_Dirs.emplace(S,  std::make_pair<int, int>(-1,0));
    //m_Dirs.emplace(SW, std::make_pair<int, int>(-1,-1));
    //m_Dirs.emplace(W, std::make_pair<int, int>(0,-1));
    //m_Dirs.emplace(NW, std::make_pair<int, int>(1,-1));

    return true; // return false if any errors actually occur, to stop engine initialization
}

void AStarPather::shutdown()
{
    /*
        Free any dynamically allocated memory or any other general house-
        keeping you need to do during shutdown.
    */
    m_OpenList.Clear();

    for (size_t i = 0; i < m_NodeList.size(); i++)
    {
        delete m_NodeList[i];
    }

    m_NodeList.clear();
}

PathResult AStarPather::compute_path(PathRequest &request)
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


    if(request.newRequest) {
        //Initialize everything.Clear Open / Closed Lists.

        //    Push Start Node onto the Open List with cost of f(x) = g(x) + h(x).
 
        if (m_CurrentMap != terrain->get_map_index())
        {
            Messenger::send_message(Messages::MAP_CHANGE);

            return PathResult::PROCESSING;
        }

        m_RequestID += 1;

        m_CurrentHeuristic = m_Heuristics[static_cast<size_t>(request.settings.heuristic)];

        m_OpenList.Clear();

        const GridPos start = terrain->get_grid_position(request.start);
        const GridPos goal = terrain->get_grid_position(request.goal);

        m_StartNode = GetNode(start.row, start.col);
        m_GoalNode = GetNode(goal.row, goal.col);


        m_OpenList.Push(m_StartNode);
    }
    //While(Open List is not empty) {
    while (!m_OpenList.Empty())
    {
        //    parentNode = Pop cheapest node off Open List.
        Node* parentNode = m_OpenList.Pop();

        if (!parentNode)
            continue;

        //If parentNode is the Goal Node, then path found(return PathResult::COMPLETE).
        if (parentNode == m_GoalNode)
        {

            if (request.settings.rubberBanding && request.settings.smoothing)
            {
                return PathResult::COMPLETE;
            }
            else if(request.settings.rubberBanding)
            {
                RubberBanding(request.path, m_GoalNode);
                return PathResult::COMPLETE;
            }
            else if ( request.settings.smoothing)
            {
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

        //For(all neighboring child nodes of parentNode) {
        for (int i = 0; i < Direction::Directions; i++)
        {
            const bool valid = (parentNode->mNeighbors & (1 << i));

            if (!valid)
                continue;

			const std::pair<int, int>& dir = m_Dirs[i];

			const int row = parentNode->gridPos.row + dir.first;
			const int col = parentNode->gridPos.col + dir.second;

			Node* neighbor = GetNode(row, col);

			const float givenCost = parentNode->givenCost + Cost(parentNode->gridPos, neighbor->gridPos);

			//Compute its cost, f(x) = g(x) + h(x)
			const float finalCost = givenCost + m_CurrentHeuristic(neighbor->gridPos, m_GoalNode->gridPos) * request.settings.weight;

			//If child node isn’t on Open or Closed list, put it on Open List.
			// or if child node is on Open or Closed List,
			if (neighbor->list == NoList || givenCost < neighbor->givenCost)
			{
				//AND this new one is cheaper,


				//then take the old expensive one off both lists and put this new
				//cheaper one on the Open List.
                const float old_cost = neighbor->finalCost;

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
				}
			}

        }

        m_OpenList.Maintain();

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


    //Open List empty, thus no path possible(return PathResult::IMPOSSIBLE).

    return PathResult::IMPOSSIBLE;
}


void AStarPather::InitializeNewMap()
{
    if (m_NodeList.empty())
    {
        AllocateMap();
        return;
    }

    m_MapWidth = terrain.get()->get_map_width();
    m_MapHeight = terrain.get()->get_map_height();

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
                const std::pair<int, int> dir = m_Dirs.at((Direction)i);


                int row = node->gridPos.row + dir.first;
                int col = node->gridPos.col + dir.second;

                if (terrain->is_valid_grid_position(row, col))
                {
                    const Node* neighbor = GetNode(row, col);

                    if (neighbor)
                    {
                        if (!terrain->is_wall(neighbor->gridPos))
                        {
                            if (dir.first != 0 && dir.second != 0)
                            {
                                const Node* newAdj = GetNode(node->gridPos.row + dir.first, node->gridPos.col);
                                const Node* newAdj2 = GetNode(node->gridPos.row, node->gridPos.col + dir.second);
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

void AStarPather::RubberBanding(WaypointList& path, Node* pHead)
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
				newPos.row =  i;
				newPos.col =  j;

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
        path.push_front(terrain->get_world_position(pathHead->gridPos));

        pathHead = pathHead->parent;
    }

}

float AStarPather::Octile(const GridPos& e, const GridPos& s)
{
    //const std::pair<int, int> ret = std::minmax(std::abs(s.row - e.row), std::abs(s.col - e.col));

    //eliminating std::abs is faster overall??????????? crazy
    const std::pair<int, int> r = std::minmax(s.col, e.col);
    const std::pair<int, int> c = std::minmax(s.row, e.row);
    const std::pair<int, int> ret = std::minmax(r.second - r.first, c.second - c.first);


    return ret.first + m_SQRT2_1*ret.second;
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

    return std::sqrtf(std::fabs(dx*dx) + std::fabs(dy*dy));
}

float AStarPather::Inconsistent(const GridPos& e, const GridPos& s)
{
    if ((s.row + s.col) % 2 > 0)
    {
        return Euclidean(e,s);
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

    
    if (node->m_RequestID != m_RequestID)
    {
        node->Reset();

        node->m_RequestID = m_RequestID;
    }

    return node;
}

void AStarPather::Queued_List::Push(Node* node)
{
    m_List.push_back(node);

    //no need to push heap since make heap puts min in the front
    //if (!std::is_heap(m_List.begin(), m_List.end()))
        //std::push_heap(m_List.begin(), m_List.begin(), NodeSorter());

    //m_List.insert(node);
}

AStarPather::Node* AStarPather::Queued_List::Pop()
{
    //make heap everytime we pop to but min in front

    std::make_heap(m_List.begin(), m_List.end(), NodeSorter()); // moves the smallest to the end

    Node* node = m_List.front();

    m_List.erase(m_List.begin());

    //Node* node = *m_List.begin();

    //m_List.erase(m_List.begin());

    return node;
}

void AStarPather::Queued_List::Update()
{
    //std::make_heap(m_List.begin(), m_List.end(), NodeSorter()); // moves the smallest to the end
}

void AStarPather::Queued_List::Clear()
{
    m_List.clear();
}

bool AStarPather::Queued_List::Empty() const
{
    return m_List.empty();
}


AStarPather::Buckets::Buckets(AStarPather* p)
{
    m_Parent = p;
    m_MaxBucket = static_cast<int>(m_Buckets.size() - 1);

    //for (size_t i = 0; i < length; i++)
    //{

    //}
}

void AStarPather::Buckets::Maintain()
{
    m_Buckets[m_CurrentLowestBucket].Update();
}

void AStarPather::Buckets::Push(Node* node)
{
    int bucket = static_cast<int>(node->finalCost / m_Range);

    bucket = std::min(bucket, m_MaxBucket);

    m_Buckets[bucket].Push(node);
    
    //set insert is expensive but too valuable.
    //m_CurrentBucket.insert(bucket);

    bool& used = m_BucketFrequency[bucket];
    if (!used)
    {
        m_CurrentBucket.push(bucket);

        used = true;
    }

    //	Update the pointer to the lowest bucket when you Pop a node

    //m_CurrentLowestBucket = *m_CurrentBucket.begin();
    m_CurrentLowestBucket = m_CurrentBucket.top();
}

AStarPather::Node* AStarPather::Buckets::Pop()
{
    return  m_Buckets[m_CurrentLowestBucket].Pop();
}

void AStarPather::Buckets::Update(Node* new_node, const float old_final_cost)
{
    ///update this new node
    int bucket = static_cast<int>(new_node->finalCost / m_Range);

    bucket = std::min(bucket, m_MaxBucket);

    //using map to track old bucket is bad


    const int old_bucket = static_cast<int>(old_final_cost / m_Range);

    //if node belongs in other bucket
    if (old_bucket != bucket)
    {

        Push(new_node);
    }
    else
    {
        m_Buckets[bucket].Update();
    }

}

void AStarPather::Buckets::Clear()
{
    //set::extract too slow


    //for (auto itr : m_CurrentBucket)
    //{
    //    m_Buckets[itr].Clear();
    //}
    //
    //m_CurrentBucket.clear();

    while (!m_CurrentBucket.empty())
    {
        int bucket = m_CurrentBucket.top();

        m_Buckets[bucket].Clear();
        m_BucketFrequency[bucket] = false;
        m_CurrentBucket.pop();
    }

    //using map to track used nodes is too slow

    //m_BucketHistory.clear();

    //if (!m_BucketHistory.empty())
    //{

    //    for (const auto& node : m_BucketHistory)
    //    {
    //        m_Parent->m_NodeList[node.first]->Reset();
    //    }

    //    m_BucketHistory.clear();
    //}


}

bool AStarPather::Buckets::Empty()
{
    if (m_Buckets[m_CurrentLowestBucket].Empty())
    {
        //(move it upward until you find a bucket with nodes).
        // 
        //auto it = std::find_if_not(m_Buckets.begin() + m_CurrentLowestBucket, m_Buckets.end(), IsEmpty);
        //m_CurrentLowestBucket = static_cast<int>(std::distance(m_Buckets.begin(), it));

        m_BucketFrequency[m_CurrentLowestBucket] = false;


        //m_CurrentBucket.erase(m_CurrentLowestBucket);
        m_CurrentBucket.pop();

        if (m_CurrentBucket.empty())
        {
            return true;
        }

        m_CurrentLowestBucket = m_CurrentBucket.top();


 /*       if (m_CurrentLowestBucket == m_Buckets.size())
        {
        }*/
    }

    return m_Buckets[m_CurrentLowestBucket].Empty();
}
