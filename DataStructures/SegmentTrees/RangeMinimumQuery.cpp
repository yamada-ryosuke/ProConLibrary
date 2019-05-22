#include <bits/stdc++.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////
// Range Minimum Query //
/////////////////////////

class RangeMinimumQuery {
private:
	std::vector<long long> container_;
	const long long inf_{LLONG_MAX};
	void build(const unsigned int array_size)
	{
		unsigned int length{1};
		while (length < array_size)
			length <<= 1;
		container_.resize(2 * length, inf_);
	}

public:
	RangeMinimumQuery(const unsigned int array_size) { build(array_size); }
	RangeMinimumQuery(const std::vector<long long> &array)
	{
		build(array.size());
		std::copy(array.begin(), array.end(), container_.begin() + (container_.size() >> 1));
		for (auto i{(container_.size() >> 1) - 1}; i > 0; i--)
			container_[i] = std::min(container_[2 * i], container_[2 * i + 1]);
	}
	// indexは0-indexed
	void update(const int index, const long long assigned)
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
	long long get(const int left, const int right) const
	{
		// ノードの番号、左端、右端
		using i3 = std::array<int, 3>;
		std::stack<i3> pre_added;
		pre_added.push({1, 0, (int)container_.size() >> 1});

		long long min{inf_};
		while (!pre_added.empty())
		{
			i3 added{pre_added.top()};
			pre_added.pop();
			if (added[2] <= left || right <= added[1])
				continue;
			
			if (left <= added[1] && added[2] <= right)
				min = std::min(min, container_[added[0]]);
			else
			{
				int mid{(added[1] + added[2]) >> 1};
				pre_added.push({2 * added[0], added[1], mid});
				pre_added.push({2 * added[0] + 1, mid, added[2]});
			}
		}
		return min;
	}
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここまでコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A
// この問題ではinf_を(1ll << 31) - 1に書き換える必要がある
int main()
{
	int n, q;
	scanf("%d%d", &n, &q);
	RangeMinimumQuery rmq(n);
	for (int i{}; i < q; i++)
	{
		int com, x, y;
		scanf("%d%d%d", &com, &x, &y);
		if (!com) rmq.update(x, y);
		else printf("%lld\n", rmq.get(x, y + 1));
	}
	return 0;
}
