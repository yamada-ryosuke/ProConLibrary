#include "UnionFind.hpp"

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A&lang=jp
int main()
{
	int n, q;
	scanf("%d%d", &n, &q);
	UnionFind uf(n);
	for (int i{}; i < q; i++)
	{
		int com, x, y;
		scanf("%d%d%d", &com, &x, &y);
		if (!com) uf.unite(x, y);
		else if (uf.areConnected(x, y))
			puts("1");
		else
			puts("0");
	}
	return 0;
}