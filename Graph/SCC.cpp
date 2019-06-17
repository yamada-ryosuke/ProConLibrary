#include <bits/stdc++.h>

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
	using v2i = std::vector<vi>;
	using vb = std::vector<bool>;

	v2i edge_, revEdge_, componentElements_;
	vi belongTo_;

	void backTrack(const int index, vi& revOrder, vb& visited)
	{
		if (visited[index]) return;
		visited[index] = true;
		for (const auto& next: edge_[index])
			backTrack(next, revOrder, visited);
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
	const vi& belongTo;
	const v2i componentElements;

	template<typename Adjacent>
	SCC(Adjacent&& adjacentList)
		: edge_(std::forward<Adjacent>(adjacentList)), belongTo(belongTo_), componentElements(componentElements_)
	{
		revEdge_.resize(edge_.size());
		for (int i{}; i < (int)edge_.size(); i++)
			for (const auto& vertex: edge_[i])
				revEdge_[vertex].push_back(i);

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

	v2i makeDAG()
	{
		std::set<std::pair<int, int>> added;
		v2i dagList(edge_.size());
		for (int from_i{}; from_i < (int)edge_.size(); from_i++)
			for (const auto& to_i: edge_[from_i])
			{
				const int dag_from{belongTo[from_i]}, dag_to{belongTo[to_i]};
				if (dag_from == dag_to || added.find({dag_from, dag_to}) != added.end())
					continue;
				dagList[dag_from].push_back(dag_to);
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
	using vi = std::vector<int>;
	std::vector<vi> edge(V);
	for (int i{}; i < E; i++)
	{
		int s, t;
		scanf("%d%d", &s, &t);
		edge[s].push_back(t);
	}
	SCC scc(std::move(edge));
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