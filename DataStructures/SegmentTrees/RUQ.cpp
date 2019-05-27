#include <bits/stdc++.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////
// Range Update Query //
////////////////////////

class RUQ {
private:
	std::vector<int64_t> num_container_, time_container_;
	const int64_t optional_{(1ll << 31) - 1};
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
	RUQ(const unsigned int array_size) { build(array_size); }
	RUQ(const std::vector<int64_t> &array)
	{
		build(array.size());
		std::copy(array.begin(), array.end(), num_container_.begin() + (num_container_.size() >> 1));
		std::fill(time_container_.begin() + ((int)time_container_.size() >> 1), time_container_.begin() + ((int)time_container_.size() >> 1) + (int)array.size(), update_num_);
		update_num_++;
	}
	// left,rightは0-indexed、[left, right)の半開区間
	void update(const int left, const int right, const int64_t assigned)
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
	int64_t get(const int index) const
	{
		int64_t last{optional_};
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


//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここまでコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E
int main()
{
	int n, q;
	scanf("%d%d", &n, &q);

	RUQ raq(n);
	for (int q_i{}; q_i < q; q_i++)
	{
		int com;
		scanf("%d", &com);
		if (com)
		{
			int i;
			scanf("%d", &i);
			printf("%lld\n", raq.get(i));
		}
		else
		{
			int s, t, x;
			scanf("%d%d%d", &s, &t, &x);
			raq.update(s, t + 1, x);
		}
	}
	return 0;
}