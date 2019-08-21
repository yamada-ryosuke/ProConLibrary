#include "SCC.hpp"

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_C&lang=jp
int main()
{
	int V, E;
	scanf("%d%d", &V, &E);
	EdgeLists edges(V);
	for (int i{}; i < E; i++)
	{
		int s, t;
		scanf("%d%d", &s, &t);
		edges[s].push_back({t});
	}
	SCC scc(edges);
	int Q;
	scanf("%d", &Q);
	for (int i{}; i < Q; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		if (scc.belongTo[u] == scc.belongTo[v])
			puts("1");
		else
			puts("0");
	}

	return 0;
}