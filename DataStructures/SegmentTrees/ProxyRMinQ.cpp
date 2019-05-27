#include <bits/stdc++.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////
// Proxy Range Minimum Query //
///////////////////////////////

class ProxyRMinQ {
private:
	// 一点操作用プロキシクラス(更新用)
	class OnePointProxy {
	private:
		ProxyRMinQ& rmq_;
		const int index_;

	public:
		OnePointProxy(ProxyRMinQ& rmq, const int index)
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
		const ProxyRMinQ& rmq_;
		const int left_, right_;

	public:
		RangeProxy(const ProxyRMinQ& rmq, const std::initializer_list<int>& span)
			: rmq_(rmq), left_(*span.begin()), right_(*(span.begin() + 1)){}
		// 取得
		operator long long() const { return rmq_.get(left_, right_); }
	};

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
	ProxyRMinQ(const unsigned int array_size) { build(array_size); }
	ProxyRMinQ(const std::vector<long long> &array)
	{
		build(array.size());
		std::copy(array.begin(), array.end(), container_.begin() + array.size());
		for (auto i{(container_.size() >> 1) - 1}; i > 0; i--)
			container_[i] = std::min(container_[2 * i], container_[2 * i + 1]);
	}
	// 引数は0-indexed
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
	// 引数は0-indexed、[l, r)の半開区間
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
	ProxyRMinQ rmq(n);
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
