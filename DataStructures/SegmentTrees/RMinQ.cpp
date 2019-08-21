#include "RMinQ.hpp"

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A
// この問題ではinf_を(1ll << 31) - 1に書き換える必要がある
int main()
{
	int n, q;
	scanf("%d%d", &n, &q);
	RMinQ rmq(n);
	for (int i{}; i < q; i++)
	{
		int com, x, y;
		scanf("%d%d%d", &com, &x, &y);
		if (!com) rmq.update(x, y);
		else printf("%lld\n", rmq.get(x, y + 1));
	}
	return 0;
}
