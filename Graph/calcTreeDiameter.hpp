#include "EdgeTemplate.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////
// 木の直径 //
/////////////

// 引数は無向の木の隣接リスト
// 戻り値は{直径の端のindex, もう一方の端のindex, 直径の長さ}
// Edgeは{to, dist}
std::tuple<int, int, decltype(Edge::dist)> calcTreeDiameter(const EdgeLists& edges)
{
	using Dist = decltype(Edge::dist);
	using pid = std::pair<int, Dist>;

	pid one_side{0, 0};
	std::stack<pid> dfs;
	dfs.push(one_side);
	std::vector<bool> visited(edges.size());

	while (!dfs.empty())
	{
		auto now{dfs.top()};
		dfs.pop();
		visited[now.first] = true;
		if (now.second > one_side.second)
			one_side = now;
		for (auto& e: edges[now.first])
			if (!visited[e.to])
				dfs.push({e.to, now.second + e.dist});
	}
	pid another_side{one_side.first, 0};
	dfs.push(another_side);
	std::fill(visited.begin(), visited.end(), false);
	while (!dfs.empty())
	{
		auto now{dfs.top()};
		dfs.pop();
		visited[now.first] = true;
		if (now.second > another_side.second)
			another_side = now;
		for (auto& e: edges[now.first])
			if (!visited[e.to])
				dfs.push({e.to, now.second + e.dist});
	}
	return std::make_tuple(one_side.first, another_side.first, another_side.second);
}