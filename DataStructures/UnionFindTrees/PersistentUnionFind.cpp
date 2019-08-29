#include"PersistentUnionFind.hpp"

// https://atcoder.jp/contests/code-thanks-festival-2017-open/tasks/code_thanks_festival_2017_h
int main()
{
	int N, M;
	scanf("%d%d", &N, &M);
	PersistentUnionFind puf(N);
	
	for (int i{}; i < M; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		a--; b--;
		puf.unite(a, b);
	}

	int Q;
	scanf("%d", &Q);
	for (int q_i{}; q_i < Q; q_i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		x--; y--;
		int left{-1}, right{M};
		while (right - left > 1)
		{
			int mid{(left + right) / 2};
			if (puf.areConnected(x, y, mid)) right = mid;
			else left = mid;
		}
		if (right == M) puts("-1");
		else printf("%d\n", right + 1);
	}

	return 0;
}