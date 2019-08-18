#include <bits/stdc++.h>

template<typename Sequence>
std::vector<int> MPAlgorithm(const Sequence& sequence)
{
	// 閉区間[0, s_i]のprefixとsuffixに共通なもののうち最長なものの長さ([0, s_i]を除く)
	std::vector<int> table(sequence.size() + 1);
	table[0] = -1;
	for (int s_i{1}; s_i < (int)table.size(); s_i++)
	{
		int last{table[s_i - 1]};
		while (last >= 0 && sequence[last] != sequence[s_i - 1]) last = table[last];
		last++;
		table[s_i] = last;
	}
	return std::move(table);
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B&lang=jp
int main()
{
	std::string T, P;
	std::cin >> T >> P;
	auto table{MPAlgorithm(P)};
	int same_length{};
	for (int t_i{}; t_i < (int)T.size(); t_i++)
	{
		while (same_length >= 0 && P[same_length] != T[t_i]) same_length = table[same_length];
		same_length++;
		if (same_length < (int)P.size()) continue;
		printf("%d\n", t_i - (int)P.size() + 1);
		same_length = table[same_length];
	}
	return 0;
}