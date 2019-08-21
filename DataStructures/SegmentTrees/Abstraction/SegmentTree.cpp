#include "SegmentTree.hpp"

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A&lang=jp
int main()
{
	int n, q;
	scanf("%d%d", &n, &q);
	auto st(
		makeSegmentTree(n,
			[](int64_t a, int64_t b){ return std::min(a, b); },
			[](int64_t a, int64_t b){ return b; },
			(1ll << 31) - 1
		)
	);

	for (int i{}; i < q; i++)
	{
		int com, x, y;
		scanf("%d%d%d", &com, &x, &y);
		if (com) printf("%lld\n", st.get(x, y + 1));
		else st.update(x, y);
	}
	return 0;
}