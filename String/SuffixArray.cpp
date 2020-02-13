#include "SuffixArray.hpp"

int main()
{
	auto sa{SuffixArray("sfadfbuieufhifiuc").result};
	for (auto& e: sa)
		printf("%d ", e);
	putchar('\n');
	return 0;
}