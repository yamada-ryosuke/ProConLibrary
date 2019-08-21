#include "RUpdRMinQ.hpp"

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_F&lang=jp
// この問題ではinf_=(1ll << 31) - 1とする必要がある
int main()
{
	int n, q;
	scanf("%d%d", &n, &q);
	RUpdRMinQ<> rurmq(n);
	for (int i{}; i < q; i++)
	{
		int com;
		scanf("%d", &com);
		if (com)
		{
			int s, t;
			scanf("%d%d", &s, &t);
			printf("%lld\n", rurmq.get(s, t + 1));
		}
		else
		{
			int s, t, x;
			scanf("%d%d%d", &s, &t, &x);
			rurmq.update(s, t + 1, x);
		}
	}
	return 0;
}