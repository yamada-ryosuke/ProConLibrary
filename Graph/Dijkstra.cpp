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

///////////////////
// ダイクストラ法 //
///////////////////

template <typename Metric = int64_t>
std::vector<Metric> dijkstra(const EdgeLists& edges, const int source)
{
	std::vector<Metric> distance(edges.size(), 1ll << 60);
	using DistPoint = std::pair<Metric, int>;
	std::priority_queue<DistPoint, std::vector<DistPoint>, std::greater<DistPoint>> pq;
	distance[source] = 0;
	pq.push({0, source});
	while (!pq.empty())
	{
		DistPoint now{pq.top()};
		pq.pop();
		if (now.first > distance[now.second]) continue;
		for (const Edge& next: edges[now.second])
			if (now.first + next.dist < distance[next.to])
			{
				distance[next.to] = now.first + next.dist;
				pq.push({distance[next.to], next.to});
			}
	}
	return std::move(distance);
}

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
	auto distance{dijkstra(edges, r)};
	
	for (int64_t& e: distance)
		if (e == (1ll << 60))
			puts("INF");
		else
			printf("%lld\n", e);
	return 0;
}