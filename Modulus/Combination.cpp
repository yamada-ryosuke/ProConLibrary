#include "Combination.hpp"

int main()
{
	for (int i{}; i < 10; i++)
	{
		printf("%lld, %lld, %lld\n", (int64_t)combi.inv[i], (int64_t)combi.fact[i], (int64_t)combi.finv[i]);
	}
	printf("%lld\n", (int64_t)combi.getCombi(5, 3));

	return 0;
}