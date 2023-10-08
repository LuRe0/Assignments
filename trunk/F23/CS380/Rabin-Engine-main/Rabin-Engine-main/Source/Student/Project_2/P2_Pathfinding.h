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



	static float Octile(const GridPos& e, const GridPos& s);
	static float Manhattan(const GridPos& e, const GridPos& s);
	static float Chebyshev(const GridPos& e, const GridPos& s);
	static float Euclidean(const GridPos& e, const GridPos& s);
	static float Inconsistent(const GridPos& e, const GridPos& s);

	float Cost(const GridPos& e, const GridPos& s);

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

		void Update();

		void Clear();


		bool Empty() const;

	private:
		std::vector<Node*> m_List;
	};


	class Buckets
	{
	public:
		Buckets(int size, AStarPather* p);

		~Buckets()
		{}

		//The size of each bucket should be tuned.Size of 1.0 is likely too big.
		//	You need to choose a data structure to hold nodes inside each bucket(like Unsorted Array or Priority Queue).
		

		  
		//	Update the pointer to the lowest bucket when you Pop a node(move it upward until you find a bucket with nodes).
		
		void Maintain();


		//	If you Push a node into a bucket lower than the current Pointer, move the Pointer to that lower bucket.
		void Push(Node* node);

		Node* Pop();

		void Update(Node* new_node);


		void Clear();

		bool Empty();


	private:

		const float m_Range = 0.0195f;

		std::vector<Queued_List> m_Buckets;

		std::unordered_map<int, int> m_BucketHistory;

		std::set<int> m_CurrentBucket;

		int m_CurrentLowestBucket = 0;

		int m_MaxBucket;

		AStarPather* m_Parent;

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

	std::unordered_map<Heuristic, std::function<float (const GridPos& e, const GridPos& s)>> m_Heuristics;

	std::function<float(const GridPos& e, const GridPos& s)> m_CurrentHeuristic;

	Buckets m_OpenList = Buckets(2310, this);

	int m_MapWidth;
	int m_MapHeight;


	unsigned m_CurrentMap;


	static bool IsEmpty(const Queued_List& list) {
		return list.Empty();
	}

	friend class Buckets;
};


