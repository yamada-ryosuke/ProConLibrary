#include "Garner.hpp"
#include "calcGCD.hpp"

int64_t solve();
void addMap(std::map<int64_t, std::pair<int, int>>&, int64_t, int, int);

// https://yukicoder.me/problems/no/187
int main()
{
	printf("%lld\n", solve());

	return 0;
}

int64_t solve()
{
	constexpr int64_t mod{1'000'000'007};
	int N;
	scanf("%d", &N);
	std::vector<int64_t> X(N), Y(N);
	for (int i{}; i < N; i++)
		scanf("%lld%lld", &X[i], &Y[i]);
	for (int i{}; i < N; i++)
		for (int j{}; j < N; j++)
		{
			if (i == j) continue;
			const int64_t gcd{calcGCD(Y[i], Y[j])};
			if (X[i] % gcd != X[j] % gcd)
				return -1;
		}
	
	// {prime, {count, index}}
	std::map<int64_t, std::pair<int, int>> primes;
	for (int i{}; i < N; i++)
	{
		int64_t cpy{Y[i]};
		for (int64_t j{2}; j * j <= cpy; j++)
		{
			if (cpy % j > 0) continue;
			int count{};
			while (cpy % j == 0)
			{
				cpy /= j;
				count++;
			}
			addMap(primes, j, count, i);
		}
		if (cpy > 1)
			addMap(primes, cpy, 1, i);
	}
	for (auto& e: primes)
		for (int i{}; i < N; i++)
		{
			if (e.second.second == i) continue;
			while (Y[i] % e.first == 0)
				Y[i] /= e.first;
		}
	for (int i{}; i < N; i++)
		X[i] %= Y[i];
	if (![&]()
		{
			for (auto& e: X)
				if (e > 0)
					return false;
			return true;
		}()
	)
		return garner(X, Y, mod);
	int64_t ans{1};
	for (auto& e: Y)
		ans = ans * e % mod;
	return ans;
}

void addMap(std::map<int64_t, std::pair<int, int>>& primes, int64_t prime, int count, int index)
{
	auto it{primes.find(prime)};
	if (it == primes.end())
		primes[prime] = {count, index};
	else if (count > it->second.first)
		it->second = {count, index};
}