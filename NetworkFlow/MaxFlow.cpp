#include <bits/stdc++.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////
// Ford-Fulkerson //
////////////////////

class MaxFlow {
private:
	using vi64 = std::vector<int64_t>;
	using Matrix = std::vector<vi64>;
	std::vector<bool> visited_;

	Matrix graph_;

	int64_t findPath(const int source, const int sink, const int node_i, const int64_t flow)
	{
		if (node_i == sink) return flow;
		visited_[node_i] = true;
		for (int next_i{}; next_i < (int)graph_.size(); next_i++)
		{
			if (!graph_[node_i][next_i] || visited_[next_i]) continue;
			const int64_t additional_flow{findPath(source, sink, next_i, std::min(flow, graph_[node_i][next_i]))};
			if (!additional_flow) continue;

			graph_[node_i][next_i] -= additional_flow;
			graph_[next_i][node_i] += additional_flow;
			return additional_flow;
		}
		return 0;
	}
public:
	MaxFlow(const int node_num)
		: graph_(node_num, vi64(node_num)), visited_(node_num){}
	void add_edge(const int from, const int to, const int64_t flow)
	{
		graph_[from][to] += flow;
	}
	int64_t operator()(const int source, const int sink)
	{
		int64_t flow_sum{};
		while (true)
		{
			std::fill(visited_.begin(),visited_.end(), false);
			int64_t additional_flow{findPath(source, sink, source, LLONG_MAX)};
			if (!additional_flow) break;
			flow_sum += additional_flow;
		}
		return flow_sum;
	}
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここまでコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A&lang=jp
int main()
{
	int V, E;
	scanf("%d%d", &V, &E);
	MaxFlow max_flow(V);

	for (int e_i{}; e_i < E; e_i++)
	{
		int u, v, c;
		scanf("%d%d%d", &u, &v, &c);
		max_flow.add_edge(u, v, c);
	}
	printf("%lld\n", max_flow(0, V - 1));
	return 0;
}