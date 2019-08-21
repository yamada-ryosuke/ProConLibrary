#include "TreeAncestor.hpp"

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C&lang=jp
int main()
{
	int n;
	scanf("%d", &n);
	EdgeLists graph(n);
	for (auto& e: graph)
	{
		int k;
		scanf("%d", &k);
		e.resize(k);
		for (auto& f: e)
			scanf("%d", &f.to);
	}
	TreeAncestor lca(graph, 0);
	int q;
	scanf("%d", &q);
	for (int i{}; i < q; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		printf("%d\n", lca.calcLCA(u, v));
	}
	return 0;
}