#include "Fraction.hpp"

class Solve {
private:

	int rc(const Fraction& frac, const int64_t product, const int rest, const int64_t& prev_denom)
	{
		if (frac == Fraction{0, 1}) return 1;
		if (rest == 0) return 0;
		int count{};
		for (int64_t denom{std::max(prev_denom, frac.inv().ceil())}; Fraction{1, denom} * rest >= frac && denom <= product; denom++)
			count += rc(frac - Fraction{1, denom}, product / denom, rest - 1, denom);
		return count;
	}

public:
	bool is_last_query{};

	Solve()
	{
		int64_t p, q, a;
		int n;
		scanf("%lld%lld%lld%d", &p, &q, &a, &n);
		if (p == 0)
		{
			is_last_query = true;
			return;
		}
		printf("%d\n", rc({p, q}, a, n, 1));
	}
};

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1131&lang=jp
int main()
{
	while (!Solve().is_last_query);

	return 0;
}