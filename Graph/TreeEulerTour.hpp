#include "EdgeTemplate.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////
// 木のオイラーツアー //
//////////////////////

// コンストラクタの引数は無向の木の隣接リスト
// Edgeは{to}
class TreeEulerTour {
private:
	using vi = std::vector<int>;
	using vvi = std::vector<vi>;

	const EdgeLists& edges_;
	const int root_;
	vi tourList_, tourEdgeList_;
	vvi inverseList_;

	void makeEulerTour(const int index, std::vector<bool> visited, const int parent)
	{
		visited[index] = true;
		if (parent >= 0) tourEdgeList_.push_back(parent);
		addList(index);
		int parent_i{-1};
		for (int edge_i{}; edge_i < (int)edges_[index].size(); edge_i++)
		{
			const Edge& edge{edges_[index][edge_i]};
			if (edge.to == parent) parent_i = edge_i;
			if (visited[edge.to]) continue;
			tourEdgeList_.push_back(edge_i);
			makeEulerTour(edge.to, visited, index);
			addList(index);
		}
		if (parent_i >= 0)
			tourEdgeList_.push_back(parent_i);
	}

	void addList(const int index)
	{
		inverseList_[index].push_back(tourList_.size());
		tourList_.push_back(index);
	}

public:
	// オイラーツアーのindexのリスト
	const vi& tourList;
	// eulerTourListの逆像
	const vvi& inverseList;
	// edges_[eulerTourList[index]][tourEdgeList[index]]はeulerTourList[index]->eulerTourList[index+1]の辺を指す
	const vi& tourEdgeList;

	TreeEulerTour(const EdgeLists& adjacentList, const int root)
		: edges_(adjacentList), root_(root), tourList(tourList_), inverseList(inverseList_), tourEdgeList(tourEdgeList_)
	{
		std::vector<bool> visited;
		inverseList_.resize(adjacentList.size());
		visited.resize(adjacentList.size());
		makeEulerTour(root_, visited, -1);
	}
};