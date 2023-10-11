#pragma once
#include "Misc/PathfindingDetails.hpp"
#include <queue>
#include <unordered_map>
#include <map>
#include <array>



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
		unsigned m_RequestID = 0;

		//bool m_IsDirty = false; // eh

		void Reset()
		{
			parent = nullptr;			// Parent
			finalCost = 0;			// Final cost f(x)
			givenCost = 0;		// Given cost g(x)
			list = NoList;			// On open/closed list?

			//m_IsDirty = false;
		}

		bool operator < (const Node& other)
		{
			return this->finalCost < other.finalCost;
		}
	};

	struct NodeSorter {
		bool operator()(const Node* n1, const Node* n2) const
		{
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

	static inline float Cost(const GridPos& e, const GridPos& s);

	inline Node* GetNode(const int row, const int col);
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

		inline void Push(Node* node);

		inline Node* Pop();

		inline void Update();

		inline void Clear();


		inline bool Empty() const;

	private:
		std::vector<Node*> m_List; 
		//std::set<Node*, decltype(std::greater<Node*>())> m_List; // lmfao a set is not going to work?
	};


	class Buckets
	{
	public:
		Buckets(AStarPather* p);

		~Buckets()
		{
		}

		//The size of each bucket should be tuned.Size of 1.0 is likely too big.
		//	You need to choose a data structure to hold nodes inside each bucket(like Unsorted Array or Priority Queue).
		

		  
		
		void Maintain();


		//	If you Push a node into a bucket lower than the current Pointer, move the Pointer to that lower bucket.
		inline void Push(Node* node);

		inline Node* Pop();

		inline void Update(Node* new_node, const float cost);

		inline size_t Size();

		inline void Clear();

		inline bool Empty();


	private:

		const float m_Range = 0.01f;

		std::array<Queued_List, 10000> m_Buckets;

		std::array<bool, 10000> m_BucketFrequency; // lmfao whats memory? ITS FREE REAL ESTATE


		//std::unordered_map<int, int> m_BucketHistory; // a map is slow

		//std::set<int> m_CurrentBucket; //nvm a set is too slow

		//priority queues for the win
		std::priority_queue <int, std::vector<int>, std::greater<int>> m_CurrentBucket;

		int m_CurrentLowestBucket = 0;

		int m_MaxBucket;

		AStarPather* m_Parent;

		size_t m_Size;

	};


private:
	//    //std::priority_queue<Node> m_OpenList;

	//};


	//to slow and does not update
	//std::priority_queue<Node*> m_NodeList;

	void AllocateMap();

	void InitializeNewMap();

	void PrecomputeNeighbors();

	//void ResetNodeData(); looping over the whole map is too slow

	void RubberBanding(WaypointList& path, Node* pHead);

	std::vector<Node*> m_NodeList;

	//nope
	//std::unordered_map<Direction, std::pair<int, int>> m_Dirs;

	const std::array<const std::pair<int, int>, Directions> m_Dirs
	{
		std::make_pair<int, int>(1,0),
		std::make_pair<int, int>(1,1),
		std::make_pair<int, int>(0,1),
		std::make_pair<int, int>(-1,1),
		std::make_pair<int, int>(-1,0),
		std::make_pair<int, int>(-1,-1),
		std::make_pair<int, int>(0,-1),
		std::make_pair<int, int>(1,-1)
	};

	//const std::array<std::function<float(const GridPos& e, const GridPos& s)>, static_cast<size_t>(Heuristic::NUM_ENTRIES)> m_Heuristics
	//{
	//	AStarPather::Octile,
	//	AStarPather::Chebyshev,
	//	AStarPather::Inconsistent,
	//	AStarPather::Manhattan,
	//	AStarPather::Euclidean
	//};


	const std::array<float (*)(const GridPos& e, const GridPos& s), static_cast<size_t>(Heuristic::NUM_ENTRIES)> m_Heuristics
	{
		AStarPather::Octile,
		AStarPather::Chebyshev,
		AStarPather::Inconsistent,
		AStarPather::Manhattan,
		AStarPather::Euclidean
	};

	//std::function<float(const GridPos& e, const GridPos& s)> m_CurrentHeuristic;

	inline static float (*m_CurrentHeuristic)(const GridPos& e, const GridPos& s);

	Buckets m_OpenList = Buckets(this);

	int m_MapWidth;
	int m_MapHeight;

	unsigned m_CurrentMap;

	int m_RequestID = -1;

	Node* m_StartNode;
	Node* m_GoalNode;

	static bool IsEmpty(const Queued_List& list) {
		return list.Empty();
	}

	friend class Buckets;
};


