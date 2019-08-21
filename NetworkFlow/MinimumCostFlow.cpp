#include "MinimumCostFlow.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここまでコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B&lang=jp
int main()
{
	int V, E;
	int64_t F;
	scanf("%d%d%lld", &V, &E, &F);
	MinCostFlow minCostFlow(V, 0, V - 1);
	for (int e_i{}; e_i < E; e_i++)
	{
		int u, v;
		int64_t c, d;
		scanf("%d%d%lld%lld", &u, &v, &c, &d);
		minCostFlow.addEdge(u, v, d, c);
	}
	int64_t cost{minCostFlow(F)};
	if (cost == LLONG_MAX) puts("-1");
	else printf("%lld\n", cost);

	return 0;
}