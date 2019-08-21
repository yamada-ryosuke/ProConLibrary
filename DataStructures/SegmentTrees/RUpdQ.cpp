#include "RUpdQ.hpp"

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E
int main()
{
	int n, q;
	scanf("%d%d", &n, &q);

	RUpdQ<> ruq(n);
	for (int q_i{}; q_i < q; q_i++)
	{
		int com;
		scanf("%d", &com);
		if (com)
		{
			int i;
			scanf("%d", &i);
			printf("%lld\n", ruq.get(i));
		}
		else
		{
			int s, t, x;
			scanf("%d%d%d", &s, &t, &x);
			ruq.update(s, t + 1, x);
		}
	}
	return 0;
}