#include "MaxFlow.hpp"

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A&lang=jp
int main()
{
	int V, E;
	scanf("%d%d", &V, &E);
	MaxFlow max_flow(V, 0 , V - 1);

	for (int e_i{}; e_i < E; e_i++)
	{
		int u, v, c;
		scanf("%d%d%d", &u, &v, &c);
		max_flow.addEdge(u, v, c);
	}
	printf("%lld\n", max_flow());
	return 0;
}