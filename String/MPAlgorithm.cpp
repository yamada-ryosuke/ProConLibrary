#include "MPAlgorithm.hpp"

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