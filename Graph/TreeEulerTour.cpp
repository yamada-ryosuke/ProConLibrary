#include "TreeEulerTour.hpp"
#include "../DataStructures/SegmentTrees/RSumQBIT.hpp"

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_D&lang=jp
int main()
{
	int n;
	scanf("%d", &n);
	EdgeLists edges(n);
	for (int i{}; i < n; i++)
	{
		int k;
		scanf("%d", &k);
		for (int j{}; j < k; j++)
		{
			int c;
			scanf("%d", &c);
			edges[i].push_back({c});
			edges[c].push_back({i});
		}
	}
	for (auto& e: edges) e.shrink_to_fit();
	
	TreeEulerTour euler(edges, 0);
	RSumQBIT rsq(euler.tourList.size());
	int q;
	scanf("%d", &q);
	for (int q_i{}; q_i < q; q_i++)
	{
		int com;
		scanf("%d", &com);
		if (com == 0)
		{
			int v, w;
			scanf("%d%d", &v, &w);
			rsq.update(euler.inverseList[v].front() - 1, w);
			rsq.update(euler.inverseList[v].back(), -w);
		}
		else
		{
			int u;
			scanf("%d", &u);
			printf("%lld\n", rsq.get(0, euler.inverseList[u].front()));
		}
	}

	return 0;
}