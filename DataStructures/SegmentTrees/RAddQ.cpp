#include "RAddQ.hpp"

int main()
{
	int n, q;
	scanf("%d%d", &n, &q);

	RAddQ<> raq(n);
	for (int q_i{}; q_i < q; q_i++)
	{
		int com;
		scanf("%d", &com);
		if (com)
		{
			int i;
			scanf("%d", &i);
			i--;
			printf("%lld\n", raq.get(i));
		}
		else
		{
			int s, t, x;
			scanf("%d%d%d", &s, &t, &x);
			raq.update(s - 1, t, x);
		}
	}
	return 0;
}