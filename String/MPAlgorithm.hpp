#include <bits/stdc++.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

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