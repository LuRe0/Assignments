#pragma once
#include "Misc/PathfindingDetails.hpp"
#include <queue>
#include <unordered_map>



class AStarPather
{
private:
	enum Direction
	{
		N,
		NE,
		E,
		SE,
		S,
		SW,
		W,
		NW,
		Directions
	};

	enum OnList
	{
		NoList,
		OpenList,
		ClosedList,

	};

	struct Node
	{
		Node* parent = nullptr;			// Parent
		GridPos gridPos;		// Node’s location
		float finalCost = 0;			// Final cost f(x)
		float givenCost = 0;		// Given cost g(x)
		OnList list = NoList;			// On open/closed list?
		byte mNeighbors{ 0 };

		void Reset()
		{
			parent = nullptr;			// Parent
			finalCost = 0;			// Final cost f(x)
			givenCost = 0;		// Given cost g(x)
			list = NoList;			// On open/closed list?
		}
	};

	struct NodeSorter {
		bool operator()(const Node* n1, const Node* n2) {
			return n1->finalCost > n2->finalCost;
		}
	};

public:
	/*
		The class should be default constructible, so you may need to define a constructor.
		If needed, you can modify the framework where the class is constructed in the
		initialize functions of ProjectTwo and ProjectThree.
	*/

	/* ************************************************** */
	// DO NOT MODIFY THESE SIGNATURES
	bool initialize();
	void shutdown();
	PathResult compute_path(PathRequest& request);
	/* ************************************************** */

	/*
		You should create whatever functions, variables, or classes you need.
		It doesn't all need to be in this header and cpp, structure it whatever way
		makes sense to you.
	*/



	static float Octile(int s_x, int s_y, int e_x, int e_y);
	static float Manhattan(int s_x, int s_y, int e_x, int e_y);
	static float Chebyshev(int s_x, int s_y, int e_x, int e_y);
	static float Euclidean(int s_x, int s_y, int e_x, int e_y);
	static float Inconsistent(int s_x, int s_y, int e_x, int e_y);

	float Cost(int s_x, int s_y, int e_x, int e_y);

	Node* GetNode(int row, int col);
	//class Buckets
	//{
	//public:
	//    Buckets();
	//    ~Buckets();


	class Queued_List
	{
	public:
		Queued_List()
		{}
		~Queued_List()
		{}

		void Push(Node* node);

		Node* Pop();

		void Update(Node* new_node);

		void Clear();

		bool Empty();

	private:
		typedef std::priority_queue<Node*, std::vector< Node* >, NodeSorter> AStar_Priority_Queue;
		AStar_Priority_Queue m_List;
	};

private:
	//    //std::priority_queue<Node> m_OpenList;

	//};


	//std::priority_queue<Node*> m_NodeList;

	void AllocateMap();

	void InitializeNewMap();

	void PrecomputeNeighbors();

	void ResetNodeData();

	std::vector<Node*> m_NodeList;

	std::unordered_map<Direction, std::pair<int, int>> m_Dirs;

	std::unordered_map<Heuristic, std::function<float (int s_x, int s_y, int e_x, int e_y)>> m_Heuristics;


	Queued_List m_OpenList;

	int m_MapWidth;
	int m_MapHeight;


	unsigned m_CurrentMap;
};


