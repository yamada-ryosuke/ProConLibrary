#include "BellmanFord.hpp"

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B&lang=jp
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
	
	if (bellmanFord.hasNegativeCycle())
		puts("NEGATIVE CYCLE");
	else
		for (auto& e: bellmanFord)
			if (e == bellmanFord.inf)
				puts("INF");
			else
				printf("%lld\n", e);
	return 0;
}