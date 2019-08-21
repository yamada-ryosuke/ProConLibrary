#include <bits/stdc++.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////
// Range Update Query //
////////////////////////

template<typename T = int64_t>
class RUpdQ {
private:
	std::vector<T> num_container_, time_container_;
	const T optional_{(1ll << 31) - 1};
	int update_num_{};

	void build(const unsigned int array_size)
	{
		unsigned int length{1};
		while (length < array_size)
			length <<= 1;
		num_container_.resize(2 * length, optional_);
		time_container_.resize(2 * length, -1);
	}

public:
	RUpdQ(const unsigned int array_size) { build(array_size); }
	RUpdQ(const std::vector<T> &array)
	{
		build(array.size());
		std::copy(array.begin(), array.end(), num_container_.begin() + (num_container_.size() >> 1));
		std::fill(time_container_.begin() + ((int)time_container_.size() >> 1), time_container_.begin() + ((int)time_container_.size() >> 1) + (int)array.size(), update_num_);
		update_num_++;
	}
	// left,rightは0-indexed、[left, right)の半開区間
	void update(const int left, const int right, const T assigned)
	{
		for (int left_i{std::max(0, left) + ((int)num_container_.size() >> 1)}, right_i{std::min((int)num_container_.size() >> 1, right) + ((int)num_container_.size() >> 1)};
			left_i < right_i; left_i >>= 1, right_i >>= 1
			)
		{
			if (left_i & 1)
			{
				num_container_[left_i] = assigned;
				time_container_[left_i] = update_num_;
				left_i++;
			}
			if (right_i & 1)
			{
				right_i--;
				num_container_[right_i] = assigned;
				time_container_[right_i] = update_num_;
			}
		}
		update_num_++;
	}
	// indexは0-indexed
	T get(const int index) const
	{
		T last{optional_};
		int last_time{-1};
		for (int assign_place{index + ((int)num_container_.size() >> 1)}; assign_place > 0; assign_place >>= 1)
			if (time_container_[assign_place] > last_time)
			{
				last = num_container_[assign_place];
				last_time = time_container_[assign_place];
			}
		return last;
	}
};