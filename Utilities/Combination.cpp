#include <bits/stdc++.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

class Combination {
private:
	const int64_t mod_;

public:
	std::vector<int64_t> inv, fact, finv;

	Combination(const int max = 20'000, const int64_t mod = 1'000'000'007)
		: mod_(mod),
		inv(max + 1), fact(max + 1), finv(max + 1)
	{
		inv[0] = inv[1] = fact[0] = fact[1] = finv[0] = finv[1] = 1;
		for (int num{2}; num <= max; num++)
		{
			inv[num] = (mod_ - inv[mod_ % num] * (mod_ / num) % mod_) % mod_;
			fact[num] = num * fact[num - 1] % mod_;
			finv[num] = inv[num] * finv[num - 1] % mod_;
		}
	}

	int64_t getCombi(const int n, const int r)
	{
		if (r < 0 || n < 0 || n - r < 0) return 0;
		return fact[n] * finv[r] % mod_ * finv[n - r] % mod_;
	}

	int64_t getPerm(const int n, const int r)
	{
		if (r < 0 || n < 0 || n - r < 0) return 0;
		return fact[n] * finv[n - r] % mod_;
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここまでコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Combination combi;
	for (int i{}; i < 10; i++)
	{
		printf("%lld, %lld, %lld\n", combi.inv[i], combi.fact[i], combi.finv[i]);
	}
	printf("%lld\n", combi.getCombi(5, 3));

	return 0;
}