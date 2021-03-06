#include "SuffixArray.hpp"

int main()
{
	std::string S;
	S.reserve(500'000);
	std::cin >> S;
	auto sa{SuffixArray(S).result};
	for (int i{1}; i < (int)sa.size(); i++)
		printf("%d%c", sa[i], i + 1 == (int)sa.size()? '\n': ' ');

	return 0;
}