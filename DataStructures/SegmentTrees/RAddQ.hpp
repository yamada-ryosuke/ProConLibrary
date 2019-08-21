#include <bits/stdc++.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////
// Range Add Query //
/////////////////////

template<typename T = int64_t>
class RAddQ {
private:
	std::vector<T> container_;

	void build(const unsigned int array_size)
	{
		unsigned int length{1};
		while (length < array_size)
			length <<= 1;
		container_.resize(2 * length);
	}

public:
	RAddQ(const unsigned int array_size) { build(array_size); }
	RAddQ(const std::vector<T> &array)
	{
		build(array.size());
		std::copy(array.begin(), array.end(), container_.begin() + (container_.size() >> 1));
		for (int i{((int)container_.size() >> 1) - 1}; i > 0; i--)
			container_[i] = container_[2 * i] + container_[2 * i + 1];
	}
	// left,rightは0-indexed、[left, right)の半開区間
	void update(const int left, const int right, const T added)
	{
		for (int left_i{std::max(0, left) + ((int)container_.size() >> 1)}, right_i{std::min((int)container_.size() >> 1, right) + ((int)container_.size() >> 1)};
			left_i < right_i; left_i >>= 1, right_i >>= 1
			)
		{
			if (left_i & 1)
			{
				container_[left_i] += added;
				left_i++;
			}
			if (right_i & 1)
			{
				right_i--;
				container_[right_i] += added;
			}
		}
	}
	// indexは0-indexed
	T get(const int index) const
	{
		T sum{};
		for (int add_place{index + ((int)container_.size() >> 1)}; add_place > 0; add_place >>= 1)
			sum += container_[add_place];
		return sum;
	}
};