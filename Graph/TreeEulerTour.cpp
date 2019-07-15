#include <bits/stdc++.h>

struct Edge {
	int to;
	// int64_t dist{1};

	// int64_t cost;
	// int from;
	// int rev_i;
};
using EdgeVec = std::vector<Edge>;
using EdgeLists = std::vector<EdgeVec>;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// コンストラクタの引数は無向の木の隣接リスト
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここまでコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////
// Range Sum Query (BIT) //
///////////////////////////

class RSumQBIT {
private:
	std::vector<int64_t> container_;

	int64_t getHelper(const int index) const
	{
		if (index < 0) return 0;
		if ((int)(container_.size()) <= index) return container_.back();
		int64_t sum{};
		for (int add_place{index}; add_place > 0; add_place -= add_place & -add_place)
			sum += container_[add_place];
		return sum;
	}

public:
	RSumQBIT(const int array_size)
		: container_(array_size + 1) {}
	// indexは0-indexed
	void update(const int index, const int64_t added)
	{
		for (int update_place{index + 1}; update_place < (int)(container_.size()); update_place += update_place & -update_place)
			container_[update_place] += added;
	}
	// left,rightは0-indexed、[left, right)の半開区間
	int64_t get(const int left, const int right) const
	{
		return -getHelper(left) + getHelper(right);
	}
};

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_D&lang=jp
int main()
{
	int n;
	scanf("%d", &n);
	EdgeLists edges(n);
	for (int i{}; i < n; i++)
	{
		int k;
		scanf("%d", &k);
		for (int j{}; j < k; j++)
		{
			int c;
			scanf("%d", &c);
			edges[i].push_back({c});
			edges[c].push_back({i});
		}
	}
	for (auto& e: edges) e.shrink_to_fit();
	
	TreeEulerTour euler(edges, 0);
	RSumQBIT rsq(euler.tourList.size());
	int q;
	scanf("%d", &q);
	for (int q_i{}; q_i < q; q_i++)
	{
		int com;
		scanf("%d", &com);
		if (com == 0)
		{
			int v, w;
			scanf("%d%d", &v, &w);
			rsq.update(euler.inverseList[v].front() - 1, w);
			rsq.update(euler.inverseList[v].back(), -w);
		}
		else
		{
			int u;
			scanf("%d", &u);
			printf("%lld\n", rsq.get(0, euler.inverseList[u].front()));
		}
	}

	return 0;
}