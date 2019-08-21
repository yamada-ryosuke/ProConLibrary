#include "SubsequenceEnumeration.hpp"

int main()
{
	std::string S("abcbca");
	Subsequence subseq(S);
	do
		std::cout << subseq.str << std::endl;
	while (subseq.next());

	return 0;
}