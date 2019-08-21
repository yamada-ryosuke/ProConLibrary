#include "RAddRSumQ.hpp"

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G&lang=jp
int main()
{
	int n, q;
	scanf("%d%d", &n, &q);
	RAddRSumQ<> lrsq(n);
	
	for (int q_i{}; q_i < q; q_i++)
	{
		int query;
		scanf("%d", &query);
		if (query == 0)
		{
			int s, t, x;
			scanf("%d%d%d", &s, &t, &x);
			s--;
			lrsq.update(s, t, x);
		}
		else
		{
			int s, t;
			scanf("%d%d", &s, &t);
			s--;
			printf("%lld\n", lrsq.get(s, t));
		}
	}
	return 0;
}