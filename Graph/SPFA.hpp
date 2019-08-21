#include "EdgeTemplate.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////
// SPFA //
//////////

// 負辺を含むグラフの最短経路アルゴリズム
// Edgeは{to, dist}
template <typename Metric = int64_t>
std::vector<Metric> SPFA(const EdgeLists& edges, const int source)
{
	std::vector<Metric> distance(edges.size(), 1ll << 60);
	using DistPoint = std::pair<Metric, int>;
	std::queue<DistPoint> updatedQueue;
	distance[source] = 0;
	updatedQueue.push({0, source});
	while (!updatedQueue.empty())
	{
		DistPoint now{updatedQueue.front()};
		updatedQueue.pop();
		if (now.first > distance[now.second]) continue;
		for (const Edge& next: edges[now.second])
			if (now.first + next.dist < distance[next.to])
			{
				distance[next.to] = now.first + next.dist;
				updatedQueue.push({distance[next.to], next.to});
			}
	}
	return std::move(distance);
}