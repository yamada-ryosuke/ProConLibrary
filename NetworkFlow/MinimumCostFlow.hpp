#include "../Graph/EdgeTemplate.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////
// 最小費用流 //
///////////////

// Edgeは{to, cost, capacity, rev_i}　25,26行目でEdgeを作成するので注意
class MinCostFlow {
private:
	const int64_t inf_{LLONG_MAX};

	EdgeLists edges;
	const int source_, sink_;

public:
	MinCostFlow(const int node_num, const int source, const int sink)
		: edges(node_num), source_(source), sink_(sink) {}
	
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
			std::vector<int64_t> distance(edges.size(), inf_);
			distance[source_] = 0;
			std::vector<int> revEdges(edges.size());
			std::queue<std::pair<int, int64_t>> que;
			que.push({source_, 0});
			while (!que.empty())
			{
				auto now{que.front()};
				que.pop();
				if (now.second > distance[now.first]) continue;
				for (Edge& edge: edges[now.first])
					if (edge.capacity > 0 && distance[now.first] + edge.cost < distance[edge.to])
					{
						distance[edge.to] = distance[now.first] + edge.cost;
						que.push({edge.to, distance[edge.to]});
						revEdges[edge.to] = edge.rev_i;
					}
			}
			if (distance[sink_] == inf_) return inf_;
			int64_t additional_flow{flow_rest};
			for (int index{sink_}; index != source_; index = edges[index][revEdges[index]].to)
			{
				Edge& revEdge{edges[index][revEdges[index]]};
				additional_flow = std::min(additional_flow, edges[revEdge.to][revEdge.rev_i].capacity);
			}
			for (int index{sink_}; index != source_; index = edges[index][revEdges[index]].to)
			{
				Edge& revEdge{edges[index][revEdges[index]]};
				edges[revEdge.to][revEdge.rev_i].capacity -= additional_flow;
				revEdge.capacity += additional_flow;
			}
			flow_rest -= additional_flow;
			min_cost += additional_flow * distance[sink_];
		}
		return min_cost;
	}
};