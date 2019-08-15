#include <bits/stdc++.h>

struct Edge {
	int to;
	int64_t dist{1};

	// int64_t cost;
	// int from;
	// int rev_i;
};
using EdgeVec = std::vector<Edge>;
using EdgeLists = std::vector<EdgeVec>;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename Metric = int64_t>
class BellmanFord {
private:
	const EdgeLists& edges_;
	const int source_;
	std::vector<Metric> distance_;
public:
	const Metric inf;

	BellmanFord(const EdgeLists& edges, const int source)
		: edges_(edges), source_(source), distance_(edges.size(), std::numeric_limits<Metric>::max()), inf(std::numeric_limits<Metric>::max())
	{
		distance_[source] = 0;
		for (int loop{}; loop < (int)edges.size(); loop++)
			for (int now{}; now < (int)edges.size(); now++)
				if (distance_[now] != inf)
					for (const Edge& next: edges[now])
						distance_[next.to] = std::min(distance_[next.to], distance_[now] + next.dist);
	}

	// get distance_
	Metric operator[](const int index) const
	{
		return distance_[index];
	}

	decltype(distance_.begin()) begin() { return distance_.begin(); }
	decltype(distance_.end()) end() { return distance_.end(); }

	// 始点から負閉路に到達しうるか
	bool negativeCycleExists() const
	{
		std::vector<Metric> latestDistance(distance_);
		for (int loop{}; loop < (int)edges_.size(); loop++)
			for (int now{}; now < (int)edges_.size(); now++)
				if (latestDistance[now] != inf)
					for (const Edge& next: edges_[now])
						latestDistance[next.to] = std::min(latestDistance[next.to], latestDistance[now] + next.dist);
		for (int i{}; i < (int)distance_.size(); i++)
			if (distance_[i] != latestDistance[i])
				return true;
		return false;
	}

	// 始点から終点のパスであって負閉路を経由するものが存在するか
	bool negativeCycleExists(const int sink) const
	{
		std::vector<Metric> latestDistance(distance_);
		for (int loop{}; loop < (int)edges_.size(); loop++)
			for (int now{}; now < (int)edges_.size(); now++)
				if (latestDistance[now] != inf)
					for (const Edge& next: edges_[now])
						latestDistance[next.to] = std::min(latestDistance[next.to], latestDistance[now] + next.dist);

		std::vector<std::vector<int>> revEdges;
		for (int from{}; from < (int)edges_.size(); from++)
			for (const Edge& edge: edges_[from])
				revEdges[edge.to].push_back(from);
		std::vector<bool> visited;
		std::queue<int> unvisited;
		visited[source_] = true;
		unvisited.push(source_);
		while (!unvisited.empty())
		{
			const int now{unvisited.front()};
			unvisited.pop();
			if (distance_[now] != latestDistance[now])
				return true;
			for (const int& next: revEdges[now])
				if (!visited[next])
				{
					visited[next] = true;
					unvisited.push(next);
				}
		}
		return false;
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここまでコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	int V, E, r;
	scanf("%d%d%d", &V, &E, &r);
	EdgeLists edges(V);
	for (int i{}; i < E; i++)
	{
		int s, t, d;
		scanf("%d%d%d", &s, &t, &d);
		edges[s].push_back({t, d});
	}
	BellmanFord<> bellmanFord(edges, r);
	
	if (bellmanFord.negativeCycleExists())
		puts("NEGATIVE CYCLE");
	else
		for (auto& e: bellmanFord)
			if (e == bellmanFord.inf)
				puts("INF");
			else
				printf("%lld\n", e);
	return 0;
}