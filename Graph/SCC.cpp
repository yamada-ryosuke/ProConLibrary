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

///////////////////
// 強連結成分分解 //
///////////////////

// コンストラクタに隣接リストを渡すと強連結成分分解する
class SCC {
private:
	using vi = std::vector<int>;
	using vvi = std::vector<vi>;
	using vb = std::vector<bool>;

	const EdgeLists& edge_;
	vvi componentElements_, revEdge_;
	vi belongTo_;

	void backTrack(const int index, vi& revOrder, vb& visited)
	{
		if (visited[index]) return;
		visited[index] = true;
		for (const auto& next: edge_[index])
			backTrack(next.to, revOrder, visited);
		revOrder.push_back(index);
	}
	void assignComponent(const int index)
	{
		if (belongTo_[index] >= 0) return;
		belongTo_[index] = componentElements_.size() - 1;
		componentElements_.back().push_back(index);
		for (const auto& next: revEdge_[index])
			assignComponent(next);
	}

public:
	// belongTo[i]は元のグラフの要素iが属している強連結成分のindex
	const vi& belongTo;
	// belongToの逆像、compoenentElements.size()は強連結成分の個数
	const vvi& componentElements;

	SCC(const EdgeLists& adjacentList)
		: edge_(adjacentList), belongTo(belongTo_), componentElements(componentElements_)
	{
		revEdge_.resize(edge_.size());
		for (int i{}; i < (int)edge_.size(); i++)
			for (const auto& vertex: edge_[i])
				revEdge_[vertex.to].push_back(i);

		vb visited(edge_.size());
		vi revOrder;
		revOrder.reserve(edge_.size());
		for (int i{}; i < (int)edge_.size(); i++)
			backTrack(i, revOrder, visited);

		belongTo_.resize(edge_.size(), -1);
		for (int i{(int)revOrder.size() - 1}; i >= 0; i--)
		{
			const int index{revOrder[i]};
			if (belongTo_[index] >= 0) continue;
			componentElements_.push_back({});
			assignComponent(index);
		}
	}

	// 強連結成分を押しつぶした時のDAGを隣接リストで返す
	EdgeLists makeDAG() const
	{
		std::set<std::pair<int, int>> added;
		EdgeLists dagList(edge_.size());
		for (int from_i{}; from_i < (int)edge_.size(); from_i++)
			for (const auto& to_e: edge_[from_i])
			{
				const int dag_from{belongTo[from_i]}, dag_to{belongTo[to_e.to]};
				if (dag_from == dag_to || added.find({dag_from, dag_to}) != added.end())
					continue;
				dagList[dag_from].push_back({dag_to});
				added.insert({dag_from, dag_to});
			}
		return std::move(dagList);
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここまでコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_C&lang=jp
int main()
{
	int V, E;
	scanf("%d%d", &V, &E);
	EdgeLists edges(V);
	for (int i{}; i < E; i++)
	{
		int s, t;
		scanf("%d%d", &s, &t);
		edges[s].push_back({t});
	}
	SCC scc(edges);
	int Q;
	scanf("%d", &Q);
	for (int i{}; i < Q; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		if (scc.belongTo[u] == scc.belongTo[v])
			puts("1");
		else
			puts("0");
	}

	return 0;
}