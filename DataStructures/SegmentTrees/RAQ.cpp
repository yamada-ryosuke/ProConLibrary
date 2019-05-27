#include <bits/stdc++.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////
// Range Add Query //
/////////////////////////

class RAQ {
private:
	std::vector<int64_t> container_;

	void build(const unsigned int array_size)
	{
		unsigned int length{1};
		while (length < array_size)
			length <<= 1;
		container_.resize(2 * length);
	}

public:
	RAQ(const unsigned int array_size) { build(array_size); }
	RAQ(const std::vector<int64_t> &array)
	{
		build(array.size());
		std::copy(array.begin(), array.end(), container_.begin() + (container_.size() >> 1));
		for (int i{((int)container_.size() >> 1) - 1}; i > 0; i--)
			container_[i] = container_[2 * i] + container_[2 * i + 1];
	}
	// left,rightは0-indexed、[left, right)の半開区間
	void update(const int left, const int right, const int64_t added)
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
	int64_t get(const int index) const
	{
		int64_t sum{};
		for (int add_place{index + ((int)container_.size() >> 1)}; add_place > 0; add_place >>= 1)
			sum += container_[add_place];
		return sum;
	}
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここまでコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


int main()
{
	int n, q;
	scanf("%d%d", &n, &q);

	RAQ raq(n);
	for (int q_i{}; q_i < q; q_i++)
	{
		int com;
		scanf("%d", &com);
		if (com)
		{
			int i;
			scanf("%d", &i);
			i--;
			printf("%lld\n", raq.get(i));
		}
		else
		{
			int s, t, x;
			scanf("%d%d%d", &s, &t, &x);
			raq.update(s - 1, t, x);
		}
	}
	return 0;
}