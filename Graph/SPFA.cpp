#include "SPFA.hpp"

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=jp
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
	auto distance{SPFA(edges, r)};
	
	for (int64_t& e: distance)
		if (e == (1ll << 60))
			puts("INF");
		else
			printf("%lld\n", e);
	return 0;
}