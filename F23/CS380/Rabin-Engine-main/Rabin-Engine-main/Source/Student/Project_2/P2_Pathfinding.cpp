#include <pch.h>
#include "Projects/ProjectTwo.h"
#include "P2_Pathfinding.h"
#define _USE_MATH_DEFINES
#include <math.h>


const float m_SQRT2 = static_cast<float>(M_SQRT2);
const int m_MAPWIDTH = 40;
const int m_MAPHEIGHT = 40;

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

    m_Heuristics.emplace(Heuristic::OCTILE, &AStarPather::Octile);
    m_Heuristics.emplace(Heuristic::CHEBYSHEV, AStarPather::Chebyshev);
    m_Heuristics.emplace(Heuristic::MANHATTAN, AStarPather::Manhattan);
    m_Heuristics.emplace(Heuristic::EUCLIDEAN, AStarPather::Euclidean);
    m_Heuristics.emplace(Heuristic::INCONSISTENT, AStarPather::Inconsistent);

    m_Dirs.emplace(N, std::make_pair<int, int>(1,0));
    m_Dirs.emplace(NE, std::make_pair<int, int>(1,1));
    m_Dirs.emplace(E, std::make_pair<int, int>(0,1));
    m_Dirs.emplace(SE, std::make_pair<int, int>(-1,1));
    m_Dirs.emplace(S, std::make_pair<int, int>(-1,0));
    m_Dirs.emplace(SW, std::make_pair<int, int>(-1,-1));
    m_Dirs.emplace(W, std::make_pair<int, int>(0,-1));
    m_Dirs.emplace(NW, std::make_pair<int, int>(1,-1));

    return true; // return false if any errors actually occur, to stop engine initialization
}

void AStarPather::shutdown()
{
    /*
        Free any dynamically allocated memory or any other general house-
        keeping you need to do during shutdown.
    */
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
    GridPos start = terrain->get_grid_position(request.start);
    GridPos goal = terrain->get_grid_position(request.goal);

    Node* goalNode = GetNode(goal.row, goal.col);
    if(request.newRequest) {
        //Initialize everything.Clear Open / Closed Lists.

        //    Push Start Node onto the Open List with cost of f(x) = g(x) + h(x).
 
        if (m_CurrentMap != terrain->get_map_index())
        {
            Messenger::send_message(Messages::MAP_CHANGE);

            return PathResult::PROCESSING;
        }

        m_CurrentHeuristic = m_Heuristics[request.settings.heuristic];

        m_OpenList.Clear();

        Node* startPos = GetNode(start.row, start.col);

        m_OpenList.Push(startPos);
    }
    //While(Open List is not empty) {
    while (!m_OpenList.Empty())
    {
        //    parentNode = Pop cheapest node off Open List.
        Node* parentNode = m_OpenList.Pop();

        //If parentNode is the Goal Node, then path found(return PathResult::COMPLETE).
        if (parentNode == goalNode)
        {
            Node* pathHead = goalNode;
            //add path to list 
            while (pathHead->parent)
            {
                request.path.push_front(terrain->get_world_position(pathHead->gridPos));

                pathHead = pathHead->parent;
            }

            request.path.push_front(terrain->get_world_position(pathHead->gridPos));

            return PathResult::COMPLETE;
        }

        //Place parentNode on the Closed List.
        parentNode->list = ClosedList;

        //For(all neighboring child nodes of parentNode) {
        for (int i = 0; i < Direction::Directions; i++)
        {
            bool valid = (parentNode->mNeighbors & (1 << i));

            if (!valid)
                continue;

			const std::pair<int, int>& dir = m_Dirs.at((Direction)i);

			int row = parentNode->gridPos.row + dir.first;
			int col = parentNode->gridPos.col + dir.second;

			Node* neighbor = GetNode(row, col);

			float givenCost = parentNode->givenCost + Cost(parentNode->gridPos, neighbor->gridPos);

			//Compute its cost, f(x) = g(x) + h(x)
			float finalCost = givenCost + m_CurrentHeuristic(neighbor->gridPos, goalNode->gridPos) * request.settings.weight;

			//If child node isn’t on Open or Closed list, put it on Open List.
			// or if child node is on Open or Closed List,
			if (neighbor->list == NoList || givenCost < neighbor->givenCost)
			{
				//AND this new one is cheaper,


				//then take the old expensive one off both lists and put this new
				//cheaper one on the Open List.
				neighbor->givenCost = givenCost;
				neighbor->finalCost = finalCost;
				neighbor->parent = parentNode;
				if (neighbor->list != OpenList)
				{
					neighbor->list = OpenList;
					m_OpenList.Push(neighbor);
				}
				else
				{
					m_OpenList.Update(neighbor);
				}
			}

        }
        if (request.settings.heuristic == Heuristic::EUCLIDEAN)
        {
            m_OpenList.Maintain();
        }

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
                std::pair<int, int> dir = m_Dirs.at((Direction)i);


                int row = node->gridPos.row + dir.first;
                int col = node->gridPos.col + dir.second;
                if (terrain->is_valid_grid_position(row, col))
                {
                    Node* neighbor = GetNode(row, col);

                    if (neighbor)
                    {
                        if (!terrain->is_wall(neighbor->gridPos))
                        {
                            if (dir.first != 0 && dir.second != 0)
                            {
                                Node* newAdj = GetNode(node->gridPos.row + dir.first, node->gridPos.col);
                                Node* newAdj2 = GetNode(node->gridPos.row, node->gridPos.col + dir.second);
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

void AStarPather::ResetNodeData()
{
    for (int i = 0; i < m_MapWidth; i++)
    {
        for (int j = 0; j < m_MapHeight; j++)
        {
            m_NodeList[i * m_MAPWIDTH + j]->Reset();
        }
    }
}

float AStarPather::Octile(const GridPos& e, const GridPos& s)
{
    float dx = static_cast<float>(s.row - e.row);
    float dy = static_cast<float>(s.col - e.col);

    return std::fmaxf(std::fabs(dx), std::fabs(dy)) + (m_SQRT2 - 1.0f) * std::fminf(std::fabs(dx), std::fabs(dy));
}

float AStarPather::Manhattan(const GridPos& e, const GridPos& s)
{
    float dx = static_cast<float>(s.row - e.row);
    float dy = static_cast<float>(s.col - e.col);

    return std::fabs(dx) + std::fabs(dy);
}

float AStarPather::Chebyshev(const GridPos& e, const GridPos& s)
{
    float dx = static_cast<float>(s.row - e.row);
    float dy = static_cast<float>(s.col - e.col);

    return std::fmaxf(std::fabs(dx), std::fabs(dy));
}

float AStarPather::Euclidean(const GridPos& e, const GridPos& s)
{
    float dx = static_cast<float>(s.row - e.row);
    float dy = static_cast<float>(s.col - e.col);

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
    if (e.row == s.row || e.col == s.col)
    {
        return 1;
    }
    else
    {
        return (m_SQRT2);
    }
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


AStarPather::Node* AStarPather::GetNode(int row, int col)
{
    return m_NodeList[row * m_MAPWIDTH + col];
}

void AStarPather::Queued_List::Push(Node* node)
{
    m_List.push_back(node);

    std::push_heap(m_List.begin(), m_List.begin(), NodeSorter());
}

AStarPather::Node* AStarPather::Queued_List::Pop()
{
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

bool AStarPather::Queued_List::Empty() const
{
    return m_List.empty();
}

AStarPather::Buckets::Buckets(int size, AStarPather* p)
{
    for (size_t i = 0; i < size; i++)
    {
        m_Buckets = std::vector<Queued_List>(size, Queued_List());
    }

    m_Parent = p;
    m_MaxBucket = size - 1;
    //m_CurrentLowestBucket = size - 1;
    //m_NextLowestBucket = size -1;
}

void AStarPather::Buckets::Maintain()
{
    m_Buckets[m_CurrentLowestBucket].Update();
}

void AStarPather::Buckets::Push(Node* node)
{
    int bucket = static_cast<int>(node->finalCost / m_Range);

    bucket = std::min(bucket, m_MaxBucket);

    m_BucketHistory.emplace(node->gridPos.row * m_MAPWIDTH + node->gridPos.col, bucket);

    m_Buckets[bucket].Push(node);

    m_CurrentBucket.insert(bucket);

    m_CurrentLowestBucket = *m_CurrentBucket.begin();
}

AStarPather::Node* AStarPather::Buckets::Pop()
{
    return  m_Buckets[m_CurrentLowestBucket].Pop();
}

void AStarPather::Buckets::Update(Node* new_node)
{
    ///update this new node
    int bucket = static_cast<int>(new_node->finalCost / m_Range);
    bucket = std::min(bucket, m_MaxBucket);
    int pos = new_node->gridPos.row * m_MAPWIDTH + new_node->gridPos.col;

    int old_bucket = m_BucketHistory.at(pos);

    //if node belongs in other bucket
    if (old_bucket != bucket)
    {
        m_BucketHistory[pos] = bucket;
        Push(new_node);
    }
    else
    {
        m_Buckets[bucket].Update();
    }

}

void AStarPather::Buckets::Clear()
{
    while (m_CurrentBucket.size() != 0)
    {
        auto i = m_CurrentBucket.extract(*m_CurrentBucket.begin());

        m_Buckets[i.value()].Clear();
    }

    for (const auto& node : m_BucketHistory)
    {
        m_Parent->m_NodeList[node.first]->Reset();
    }

    m_BucketHistory.clear();
}

bool AStarPather::Buckets::Empty()
{
    if (m_Buckets[m_CurrentLowestBucket].Empty())
    {
        //auto it = std::find_if_not(m_Buckets.begin() + m_CurrentLowestBucket, m_Buckets.end(), IsEmpty);
        //m_CurrentLowestBucket = static_cast<int>(std::distance(m_Buckets.begin(), it));
        m_CurrentBucket.erase(m_CurrentLowestBucket);
        m_CurrentLowestBucket = *m_CurrentBucket.begin();

        if (m_CurrentBucket.empty())
        {
            return true;
        }
 /*       if (m_CurrentLowestBucket == m_Buckets.size())
        {
        }*/
    }

    return m_Buckets[m_CurrentLowestBucket].Empty();
}