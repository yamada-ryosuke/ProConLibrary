#include <bits/stdc++.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename Sequence>
std::vector<int> manacher(const Sequence& sequence)
{
	std::vector<int> table(sequence.size());
	int center{}, length{};
	while (center < (int)sequence.size())
	{
		while (center - length >= 0 && center + length < (int)sequence.size() && sequence[center - length] == sequence[center + length])
			length++;
		table[center] = length;
		int diff{1};
		while (center - diff >= 0 && center + diff < (int)sequence.size() && table[center - diff] + diff < length)
		{
			table[center + diff] = table[center - diff];
			diff++;
		}
		center += diff;
		length -= diff;
	}
	return std::move(table);
}