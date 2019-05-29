#include <bits/stdc++.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////
// 抽象化セグメント木 //
//////////////////////

// モノイドを扱えるが半群は扱えない
// identityはその演算の単位元としてのみ使用されるので、minの単位元としてINT64_MAXなどが許される
// std::minをそのまま渡してもオーバーロードを解決できないのでlambda式で包む必要がある
template <typename T, typename Operation_t, typename Update_t>
class SegmentTree {
private:

	std::vector<T> container_;
	// モノイドの演算
	Operation_t operate_;
	// 更新する値を返す
	Update_t assign_;
	// モノイドの単位元
	T identity_;

	void build(const unsigned int array_size)
	{
		unsigned int length{1};
		while (length < array_size)
			length <<= 1;
		container_.resize(2 * length, identity_);
	}

	// デバッグ用出力関数(中身は適宜編集)
	void debugOutput()
	{
		int line_break{2};
		for (int i{1}; i < (int)container_.size(); i++)
		{
			// std::cout << container_[i] << ' ';
			if (i + 1 == line_break)
			{
				putchar('\n');
				line_break *= 2;
			}
		}
	}

public:
	SegmentTree(const unsigned int array_size, Operation_t operate, Update_t assign, T identity)
		: operate_(operate), assign_(assign), identity_(identity)
	{
		build(array_size);
	}
	SegmentTree(const std::vector<T> &array, Operation_t operate, Update_t assign, T identity)
		: operate_(operate), assign_(assign), identity_(identity)
	{
		build(array.size());
		std::copy(array.begin(), array.end(), container_.begin() + (container_.size() >> 1));

		for (unsigned int i{(container_.size() >> 1) - 1}; i > 0; i--)
			container_[i] = operate_(container_[2 * i], container_[2 * i + 1]);
	}

	// 配列のindex(0-indexed)の要素にoperandを代入
	void update(const int index, const T operand)
	{
		unsigned int container_i{((unsigned int)container_.size() >> 1) + index};
		container_[container_i] = assign_(container_[container_i], operand);
		for (container_i >>= 1; container_i > 0; container_i >>= 1)
			container_[container_i] = operate_(container_[2 * container_i], container_[2 * container_i + 1]);
	}

	// 配列内の半開区間[l,r)(0-indexed)の総和を返す
	T get(const int left, const int right) const
	{
		T sum{identity_};
		for (int left_i{std::max(0, left) + ((int)container_.size() >> 1)}, right_i{std::min((int)container_.size() >> 1, right) + ((int)container_.size() >> 1)};
			left_i < right_i; left_i >>= 1, right_i >>= 1
			)
		{
			if (left_i & 1)
			{
				sum = operate_(sum, container_[left_i]);
				left_i++;
			}
			if (right_i & 1)
			{
				right_i--;
				sum = operate_(sum, container_[right_i]);
			}
		}
		return sum;
	}
};

// 引数のlambda式の型はstd::functionを使うと遅くなるため、クラステンプレートで指定したい。
// しかしlambda式の型は直接取り出せないため型推論によって型を決定しなければならない。
// しかしC++14にはクラステンプレートには型推論がないため普通の方法で宣言することはできない。
// そのため関数の型推論を利用してクラスを作成し、戻り値をautoで受けることで実質的なクラステンプレートの型推論を実現している。
template <typename T, typename Operation_t, typename Update_t>
decltype(auto) makeSegmentTree(const unsigned int array_size, Operation_t operate, Update_t assign, T identity)
{
	return SegmentTree<T, Operation_t, Update_t>(array_size, operate, assign, identity);
}

template <typename T, typename Operation_t, typename Update_t>
decltype(auto) makeSegmentTree(const std::vector<T> &array, Operation_t operate, Update_t assign, T identity)
{
	return SegmentTree<T, Operation_t, Update_t>(array, operate, assign, identity);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここまでコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A&lang=jp
int main()
{
	int n, q;
	scanf("%d%d", &n, &q);
	auto st(
		makeSegmentTree(n,
			[](int64_t a, int64_t b){ return std::min(a, b); },
			[](int64_t a, int64_t b){ return b; },
			(1ll << 31) - 1
		)
	);

	for (int i{}; i < q; i++)
	{
		int com, x, y;
		scanf("%d%d%d", &com, &x, &y);
		if (com) printf("%lld\n", st.get(x, y + 1));
		else st.update(x, y);
	}
	return 0;
}