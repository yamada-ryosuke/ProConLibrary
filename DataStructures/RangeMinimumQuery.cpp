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
	void constructorHelper(const unsigned int array_size)
	{
		unsigned int length{1};
		while (length < array_size)
			length <<= 1;
		container_.resize(2 * length, inf);
	}
	long long getHelper(const int index, const int node_l, const int node_r, const int query_l, const int query_r) const
	{
		if (query_r <= node_l || node_r <= query_l) return inf_;
		if (query_l <= node_l && node_r <= query_r) return container_[index];
		const int node_m{(node_l + node_r) >> 1};
		return std::min(getHelper(2 * index, node_l, node_m, query_l, query_r), getHelper(2 * index + 1, node_m, node_r, query_l, query_r));
	}

public:
	RangeMinimumQuery(const unsigned int array_size) { constructorHelper(array_size); }
	RangeMinimumQuery(const std::vector<long long> &array)
	{
		constructorHelper(array.size());
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
		return getHelper(1, 0, container_.size() >> 1, left, right);
	}
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここまでコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A
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
