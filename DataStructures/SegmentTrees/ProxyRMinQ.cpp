#include "ProxyRMinQ.hpp"

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A
int main()
{
	int n, q;
	scanf("%d%d", &n, &q);
	ProxyRMinQ<> rmq(n);
	for (int i{}; i < q; i++)
	{
		int com, x, y;
		scanf("%d%d%d", &com, &x, &y);
		if (!com) rmq[x] = y;
		// printfを使う場合は型情報が消えており暗黙キャストされないため、明示的にキャストする必要があることに注意
		else std::cout << rmq[{x, y + 1}] << std::endl;
	}
	return 0;
}
