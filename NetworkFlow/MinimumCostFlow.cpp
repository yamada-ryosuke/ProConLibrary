#include <bits/stdc++.h>

struct Edge {
	int to;

	int64_t cost;
	int64_t capacity;
	int rev_i;
};

using EdgeVec = std::vector<Edge>;
using EdgeLists = std::vector<EdgeVec>;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////
// 最小費用流 //
///////////////

class MinCostFlow {
private:
	const int64_t inf_{LLONG_MAX};

	EdgeLists edges;
	const int source_, sink_;
	std::vector<int64_t> distance_;
	std::vector<bool> visited_;

	void calcDistance()
	{
		std::fill(distance_.begin(), distance_.end(), inf_);
		distance_[source_] = 0;
		std::queue<std::pair<int, int64_t>> que;
		que.push({source_, 0});
		while (!que.empty())
		{
			auto now{que.front()};
			que.pop();
			if (now.second > distance_[now.first]) continue;
			for (Edge& edge: edges[now.first])
				if (edge.capacity > 0 && distance_[now.first] + edge.cost < distance_[edge.to])
				{
					distance_[edge.to] = distance_[now.first] + edge.cost;
					que.push({edge.to, distance_[edge.to]});
				}
		}
	}

	int64_t calcCapacity(const int index, const int64_t flow)
	{
		if (index == source_) return flow;
		visited_[index] = true;
		for (Edge& prev_node: edges[index])
		{
			Edge& rev_edge{edges[prev_node.to][prev_node.rev_i]};
			if (visited_[prev_node.to] || rev_edge.capacity == 0 || distance_[prev_node.to] + rev_edge.cost != distance_[index]) continue;
			const int64_t additional_flow{calcCapacity(prev_node.to, std::min(flow, rev_edge.capacity))};
			if (additional_flow == 0) continue;
			prev_node.capacity += additional_flow;
			rev_edge.capacity -= additional_flow;
			return additional_flow;
		}
		return 0;
	}

public:
	MinCostFlow(const int node_num, const int source, const int sink)
		: edges(node_num), distance_(node_num), visited_(node_num), source_(source), sink_(sink) {}
	
	void addEdge(const int from, const int to, const int64_t cost, const int capacity)
	{
		edges[from].push_back({to, cost, capacity, (int)edges[to].size()});
		edges[to].push_back({from, -cost, 0, (int)edges[from].size() - 1});
	}

	int64_t operator()(const int64_t flow)
	{
		int64_t min_cost{};
		for (int64_t flow_rest{flow}; flow_rest > 0;)
		{
			calcDistance();
			if (distance_[sink_] == inf_) return inf_;
			std::fill(visited_.begin(), visited_.end(), false);
			int64_t additional_flow{calcCapacity(sink_, flow_rest)};
			flow_rest -= additional_flow;
			min_cost += additional_flow * distance_[sink_];
		}
		return min_cost;
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここまでコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B&lang=jp
int main()
{
	int V, E;
	int64_t F;
	scanf("%d%d%lld", &V, &E, &F);
	MinCostFlow minCostFlow(V, 0, V - 1);
	for (int e_i{}; e_i < E; e_i++)
	{
		int u, v;
		int64_t c, d;
		scanf("%d%d%lld%lld", &u, &v, &c, &d);
		minCostFlow.addEdge(u, v, d, c);
	}
	int64_t cost{minCostFlow(F)};
	if (cost == LLONG_MAX) puts("-1");
	else printf("%lld\n", cost);

	return 0;
}