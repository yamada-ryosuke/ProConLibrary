#include "EdgeTemplate.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////
// ダイクストラ法 //
///////////////////

// 負辺を含まないグラフの最短経路アルゴリズム
// Edgeは{to, dist}
decltype(auto) dijkstra(const EdgeLists& edges, const int source)
{
	using Metric = decltype(Edge::dist);
	std::vector<Metric> distance(edges.size(), std::numeric_limits<Metric>::max());
	using DistPoint = std::pair<Metric, int>;
	std::priority_queue<DistPoint, std::vector<DistPoint>, std::greater<DistPoint>> updatedQueue;
	distance[source] = 0;
	updatedQueue.push({0, source});
	while (!updatedQueue.empty())
	{
		DistPoint now{updatedQueue.top()};
		updatedQueue.pop();
		if (now.first > distance[now.second]) continue;
		for (const Edge& next: edges[now.second])
			if (now.first + next.dist < distance[next.to])
			{
				distance[next.to] = now.first + next.dist;
				updatedQueue.push({distance[next.to], next.to});
			}
	}
	return distance;
}