#include "UnionFindWithPotential.hpp"

bool solve()
{
	int N, M;
	scanf("%d%d", &N, &M);
	UnionFindWithPotential ufp(N);
	for (int i{}; i < M; i++)
	{
		int L, R;
		long long D;
		scanf("%d%d%lld", &L, &R, &D);
		L--; R--;
		if (!ufp.unite(R, L, D)) return false;
	}
	return true;
}

// https://atcoder.jp/contests/abc087/tasks/arc090_b
int main()
{
	if (solve()) puts("Yes");
	else puts("No");

	return 0;
}

// // http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B&lang=jp
// int main()
// {
// 	int n, q;
// 	scanf("%d%d", &n, &q);
// 	UnionFindWithPotential ufp(n);
// 	for (int q_i{}; q_i < q; q_i++)
// 	{
// 		int query, x, y;
// 		scanf("%d%d%d", &query, &x, &y);
// 		if (query == 0)
// 		{
// 			int z;
// 			scanf("%d", &z);
// 			ufp.unite(y, x, z);
// 		}
// 		else if (ufp.areConnected(x, y))
// 			printf("%lld\n", ufp.calcDiff(y, x));
// 		else
// 			puts("?");
// 	}
// 	return 0;
// }