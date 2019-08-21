#include "DualSegmentTree.hpp"

int main()
{
	int n, q;
	scanf("%d%d", &n, &q);
	auto dst(
		makeDualSegmentTree(
			n,
			[](const int64_t left, const int64_t right)
			{
				return left >= 0?left:right;
			},
			-1ll,
			[](const int64_t monoid)
			{
				return [=](const int64_t argument)
				{
					return monoid >= 0? monoid: argument;
				};
			}
		)
	);

	for (int q_i{}; q_i < q; q_i++)
	{
		int com;
		scanf("%d", &com);
		if (com)
		{
			int i;
			scanf("%d", &i);
			printf("%lld\n", dst.get(i)((1ll << 31) - 1));
		}
		else
		{
			int s, t, x;
			scanf("%d%d%d", &s, &t, &x);
			t++;
			dst.update(s, t, x);
		}
	}

	return 0;
}