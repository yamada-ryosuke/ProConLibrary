#include <bits/stdc++.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////
// Proxy Range Minimum Query //
///////////////////////////////

template<typename T = int64_t>
class ProxyRMinQ {
private:
	// 一点操作用プロキシクラス(更新用)
	class OnePointProxy {
	private:
		ProxyRMinQ<T>& rmq_;
		const int index_;

	public:
		OnePointProxy(ProxyRMinQ<T>& rmq, const int index)
			: rmq_(rmq), index_(index){}
		// 値変更
		OnePointProxy &operator=(const T assigned)
		{
			rmq_.update(index_, assigned);
			return *this;
		}
	};
	// 区間操作用プロキシクラス(取得用)
	class RangeProxy {
	private:
		const ProxyRMinQ<T>& rmq_;
		const int left_, right_;

	public:
		RangeProxy(const ProxyRMinQ<T>& rmq, const std::initializer_list<int>& span)
			: rmq_(rmq), left_(*span.begin()), right_(*(span.begin() + 1)){}
		// 取得
		operator T() const { return rmq_.get(left_, right_); }
	};

	std::vector<T> container_;
	const T inf_{LLONG_MAX};

	void build(const unsigned int array_size)
	{
		unsigned int length{1};
		while (length < array_size)
			length <<= 1;
		container_.resize(2 * length, inf_);
	}

public:
	ProxyRMinQ(const unsigned int array_size) { build(array_size); }
	ProxyRMinQ(const std::vector<T> &array)
	{
		build(array.size());
		std::copy(array.begin(), array.end(), container_.begin() + array.size());
		for (auto i{(container_.size() >> 1) - 1}; i > 0; i--)
			container_[i] = std::min(container_[2 * i], container_[2 * i + 1]);
	}
	// 引数は0-indexed
	void update(const int index, const T assigned)
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
	T get(const int left, const int right) const
	{
		T min{inf_};
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
	// 引数は0-indexed
	OnePointProxy operator[](const int index) { return OnePointProxy(*this, index); }
	// 引数は0-indexed、[l, r)の半開区間
	RangeProxy operator[](const std::initializer_list<int> span) const { return RangeProxy(*this, span); }
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここまでコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A
int main()
{
	int n, q;
	scanf("%d%d", &n, &q);
	ProxyRMinQ<> rmq(n);
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
