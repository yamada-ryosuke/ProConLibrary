#include "SubsequenceAutomaton.hpp"

int64_t solve();

// https://atcoder.jp/contests/abc138/tasks/abc138_e
int main()
{
	printf("%lld\n", solve());

	return 0;
}

int64_t solve()
{
	std::string s, t;
	std::cin >> s >> t;
	auto table{subsequenceAutomaton(s)};
	int now{};
	int64_t ans{};
	for (char& e: t)
	{
		int next{table[now][e - 'a']};
		if (next == (int)table.size() - 1)
		{
			ans += (int)s.size();
			next = table[0][e - 'a'];
		}
		if (next == (int)table.size() - 1)
			return -1ll;
		now = next;
	}
	ans += now;
	return ans;
}