#include <bits/stdc++.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////
// Range Minimum Query //
/////////////////////////

class RMinQ {
private:
	std::vector<int64_t> container_;
	const int64_t inf_{LLONG_MAX};

	void build(const unsigned int array_size)
	{
		unsigned int length{1};
		while (length < array_size)
			length <<= 1;
		container_.resize(2 * length, inf_);
	}

public:
	RMinQ(const unsigned int array_size) { build(array_size); }
	RMinQ(const std::vector<int64_t> &array)
	{
		build(array.size());
		std::copy(array.begin(), array.end(), container_.begin() + (container_.size() >> 1));
		for (auto i{(container_.size() >> 1) - 1}; i > 0; i--)
			container_[i] = std::min(container_[2 * i], container_[2 * i + 1]);
	}
	// indexは0-indexed
	void update(const int index, const int64_t assigned)
	{
		auto update_place{(container_.size() >> 1) + index};
		container_[update_place] = assigned;
		while (update_place > 1)
		{
			update_place >>= 1;
			container_[update_place] = std::min(container_[2 * update_place], container_[2 * update_place + 1]);
		}
	}
	// left,rightは0-indexed、[left, right)の半開区間
	int64_t get(const int left, const int right) const
	{
		int64_t min{inf_};
		for (int left_i{std::max(0, left) + ((int)container_.size() >> 1)}, right_i{std::min((int)container_.size() >> 1, right) + ((int)container_.size() >> 1)};
			left_i < right_i; left_i >>= 1, right_i >>= 1
			)
		{
			if (left_i & 1)
			{
				min = std::min(min, container_[left_i]);
				left_i++;
			}
			if (right_i & 1)
			{
				right_i--;
				min = std::min(min, container_[right_i]);
			}
		}
		return min;
	}
};