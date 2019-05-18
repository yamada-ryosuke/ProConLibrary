#include <bits/stdc++.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////
// Range Minimum Query with Proxy //
////////////////////////////////////

class RangeMinimumQueryWithProxy {
private:
	std::vector<long long> container_;
	void constructorHelper(const unsigned int array_size)
	{
		unsigned int length{1};
		while (length < array_size)
			length <<= 1;
		container_.resize(2 * length, 1ll << 60);
	}
	long long getHelper(const int index, const int node_l, const int node_r, const int query_l, const int query_r) const
	{
		if (query_r <= node_l || node_r <= query_l) return 1ll << 60;
		if (query_l <= node_l && node_r <= query_r) return container_[index];
		const int node_m{(node_l + node_r) >> 1};
		return std::min(getHelper(2 * index, node_l, node_m, query_l, query_r), getHelper(2 * index + 1, node_m, node_r, query_l, query_r));
	}

public:
	// 一点操作用プロキシクラス(更新用)
	class OnePointProxy {
	private:
		RangeMinimumQueryWithProxy& rmq_;
		const int index_;

	public:
		OnePointProxy(RangeMinimumQueryWithProxy& rmq, const int index)
			: rmq_(rmq), index_(index){}
		// 値変更
		OnePointProxy &operator=(const long long assigned)
		{
			rmq_.update(index_, assigned);
			return *this;
		}
	};
	// 区間操作用プロキシクラス(取得用)
	class RangeProxy {
	private:
		const RangeMinimumQueryWithProxy& rmq_;
		const int left_, right_;

	public:
		RangeProxy(const RangeMinimumQueryWithProxy& rmq, const std::initializer_list<int>& span)
			: rmq_(rmq), left_(*span.begin()), right_(*(span.begin() + 1)){}
		// 取得
		operator long long() const { return rmq_.get(left_, right_); }
	};
	RangeMinimumQueryWithProxy(const unsigned int array_size) { constructorHelper(array_size); }
	RangeMinimumQueryWithProxy(const std::vector<long long> &array)
	{
		constructorHelper(array.size());
		std::copy(array.begin(), array.end(), container_.begin() + array.size());
		for (auto i{(container_.size() >> 1) - 1}; i > 0; i--)
			container_[i] = std::min(container_[2 * i], container_[2 * i + 1]);
	}
	// 引数は0-indexed
	void update(const int index, const int assigned)
	{
		auto update_place{(container_.size() >> 1) + index};
		container_[update_place] = assigned;
		while (update_place > 1)
		{
			update_place >>= 1;
			container_[update_place] = std::min(container_[2 * update_place], container_[2 * update_place + 1]);
		}
	}
	// 引数は0-indexed、[l, r)の半開区間
	long long get(const int left, const int right) const
	{
		return getHelper(1, 0, container_.size() >> 1, left, right);
	}
	// 引数は0-indexed
	OnePointProxy operator[](const int index) { return OnePointProxy(*this, index); }
	// 引数は0-indexed、[l, r)の半開区間
	RangeProxy operator[](const std::initializer_list<int> span) const { return RangeProxy(*this, span); }
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A
int main()
{
	int n, q;
	scanf("%d%d", &n, &q);
	RangeMinimumQueryWithProxy rmq(n);
	for (int i{}; i < q; i++)
	{
		int com, x, y;
		scanf("%d%d%d", &com, &x, &y);
		if (!com) rmq[x] = y;
		// printfを使う場合は型情報が消えており暗黙キャストされないため、明示的にキャストする必要があることに注意
		else std::cout << rmq[{x, y + 1}] << std::endl;
	}
	return 0;
}