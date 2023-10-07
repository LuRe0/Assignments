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


        m_OpenList.Clear();


        ResetNodeData();

        Node* startPos = GetNode(start.row, start.col);

        m_OpenList.Push(startPos);
		terrain->set_color(start, Colors::Orange);
		terrain->set_color(goal, Colors::Orange);

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
            return PathResult::COMPLETE;
        }

        //Place parentNode on the Closed List.
        parentNode->list = ClosedList;

        //For(all neighboring child nodes of parentNode) {
        for (int i = 0; i < Direction::Directions; i++)
        {
            bool valid = (parentNode->mNeighbors & (1 << i));

            if (valid)
            {
                std::pair<int, int> dir = m_Dirs.at((Direction)i);

                int row = parentNode->gridPos.row + dir.first;
                int col = parentNode->gridPos.col + dir.second;

                Node* neighbor = GetNode(row, col);
                if (!neighbor)
                    continue;

            
                float givenCost = parentNode->givenCost + Cost(parentNode->gridPos.row, parentNode->gridPos.col, neighbor->gridPos.row, neighbor->gridPos.col);

                //Compute its cost, f(x) = g(x) + h(x)
                float finalCost = givenCost + m_Heuristics[request.settings.heuristic]
                                        (neighbor->gridPos.row, neighbor->gridPos.col, goalNode->gridPos.row, goalNode->gridPos.col) * request.settings.weight;

                //If child node isn’t on Open or Closed list, put it on Open List.
                if (neighbor->list == NoList)
                {
                    neighbor->givenCost = givenCost;
                    neighbor->finalCost = finalCost;
                    neighbor->list = OpenList;
                    neighbor->parent = parentNode;
                    m_OpenList.Push(neighbor);
                }
                //Else if child node is on Open or Closed List,
                else if (givenCost < neighbor->givenCost)
                {
                    //AND this new one is cheaper,
                    

					//then take the old expensive one off both lists and put this new
					//cheaper one on the Open List.
                    neighbor->givenCost = givenCost;
                    neighbor->finalCost = finalCost;
                    neighbor->parent = parentNode;
					if (neighbor->list == ClosedList)
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

    //    }
    //    If taken too much time this frame(or if request.settings.singleStep == true),
    //        abort search for now and resume next frame(return PathResult::PROCESSING).
    //}
    //Open List empty, thus no path possible(return PathResult::IMPOSSIBLE).


    
    // Just sample code, safe to delete
    //GridPos start = terrain->get_grid_position(request.start);
    //GridPos goal = terrain->get_grid_position(request.goal);
    //terrain->set_color(start, Colors::Orange);
    //terrain->set_color(goal, Colors::Orange);
    //request.path.push_back(request.start);
    //request.path.push_back(request.goal);
    //return PathResult::COMPLETE;

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

    ResetNodeData();

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

float AStarPather::Octile(int s_x, int s_y, int e_x, int e_y)
{
    float dx = static_cast<float>(s_x - e_x);
    float dy = static_cast<float>(s_y - e_y);

    return std::fmaxf(std::fabs(dx), std::fabs(dy)) + (m_SQRT2 - 1.0f) * std::fminf(std::fabs(dx), std::fabs(dy));
}

float AStarPather::Manhattan(int s_x, int s_y, int e_x, int e_y)
{
    float dx = static_cast<float>(s_x - e_x);
    float dy = static_cast<float>(s_y - e_y);

    return std::fabs(dx) + std::fabs(dy);
}

float AStarPather::Chebyshev(int s_x, int s_y, int e_x, int e_y)
{
    float dx = static_cast<float>(s_x - e_x);
    float dy = static_cast<float>(s_y - e_y);

    return std::fmaxf(std::fabs(dx), std::fabs(dy));
}

float AStarPather::Euclidean(int s_x, int s_y, int e_x, int e_y)
{
    float dx = static_cast<float>(s_x - e_x);
    float dy = static_cast<float>(s_y - e_y);

    return std::fabs(dx) + std::fabs(dy);
}

float AStarPather::Inconsistent(int s_x, int s_y, int e_x, int e_y)
{
    if ((s_x + s_y) % 2 > 0)
    {
        return Euclidean(s_x, s_y, e_x, e_y);
    }

    return 0;
}

float AStarPather::Cost(int s_x, int s_y, int e_x, int e_y)
{
    if (e_x == s_x || e_y == s_y)
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
    if (terrain->is_valid_grid_position(row, col))
    {
        return m_NodeList[row * m_MAPWIDTH + col];
    }

    return nullptr;
}

void AStarPather::Queued_List::Push(Node* node)
{
    m_List.emplace(node);
}

AStarPather::Node* AStarPather::Queued_List::Pop()
{
    Node* node = m_List.top();
    m_List.pop();


    return node;
}

void AStarPather::Queued_List::Update(Node* new_node)
{
    AStar_Priority_Queue temp = m_List;

    Clear();
    m_List.emplace(new_node);

    while (!temp.empty())
    {
        Node* node = temp.top();
        if (node->gridPos != new_node->gridPos)
        {
            m_List.emplace(node);
        }

        temp.pop();
    }

}

void AStarPather::Queued_List::Clear()
{
    while (!m_List.empty())
    {
        m_List.pop();
    }
}

bool AStarPather::Queued_List::Empty()
{
    return m_List.empty();
}
