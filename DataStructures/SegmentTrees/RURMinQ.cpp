#include <bits/stdc++.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////
// Range Update Range Minimum Query //
//////////////////////////////////////

class RURMinQ {
private:
	std::vector<int64_t> real_container_, lazy_container_;
	const int64_t inf_{LLONG_MAX};

	void build(const unsigned int array_size)
	{
		unsigned int length{1};
		while (length < array_size)
			length <<= 1;
		real_container_.resize(2 * length, inf_);
		lazy_container_.resize(2 * length, inf_);
	}

	void lazyEvaluate(int node_i)
	{
		if (lazy_container_[node_i] == inf_) return;
		if (2 * node_i < (int)real_container_.size())
			lazy_container_[2 * node_i] = lazy_container_[2 * node_i + 1] = lazy_container_[node_i];
		real_container_[node_i] = lazy_container_[node_i];
		lazy_container_[node_i] = inf_;
	}

	void updateHelper(const int query_l, const int query_r, const int assigned, const int node_i, const int node_l, const int node_r)
	{
		if (query_r <= node_l || node_r <= query_l)
			lazyEvaluate(node_i);
		else if (query_l <= node_l && node_r <= query_r)
		{
			lazy_container_[node_i] = assigned;
			lazyEvaluate(node_i);
		}
		else
		{
			lazyEvaluate(node_i);

			const int node_m{(node_l + node_r) >> 1};
			updateHelper(query_l, query_r, assigned, 2 * node_i, node_l, node_m);
			updateHelper(query_l, query_r, assigned, 2 * node_i + 1, node_m, node_r);

			real_container_[node_i] = std::min(real_container_[2 * node_i], real_container_[2 * node_i + 1]);
		}
	}

	// デバッグ用出力関数(中身は適宜編集)
	void debugOutput()
	{
		int line_break{2};
		for (int i{1}; i < (int)real_container_.size(); i++)
		{
			std::cout << real_container_[i] << ' ';
			if (i + 1 == line_break)
			{
				putchar('\n');
				line_break *= 2;
			}
		}
		line_break = 2;
		for (int i{1}; i < (int)real_container_.size(); i++)
		{
			std::cout << lazy_container_[i] << ' ';
			if (i + 1 == line_break)
			{
				putchar('\n');
				line_break *= 2;
			}
		}
	}

public:
	RURMinQ(const unsigned int array_size) { build(array_size); }
	RURMinQ(const std::vector<int64_t> &array)
	{
		build(array.size());
		std::copy(array.begin(), array.end(), real_container_.begin() + (real_container_.size() >> 1));
		for (int i{((int)real_container_.size() >> 1) - 1}; i > 0; i--)
			real_container_[i] = std::min(real_container_[2 * i], real_container_[2 * i + 1]);
	}
	// left,rightは0-indexed、[left, right)の半開区間
	void update(const int left, const int right, const int64_t assigned)
	{
		updateHelper(left, right, assigned, 1, 0, (int)real_container_.size() >> 1);
	}
	// left,rightは0-indexed、[left, right)の半開区間
	int64_t get(const int left, const int right)
	{
		// ノードの番号、左端、右端
		using NodeInfo = std::array<int, 3>;
		std::stack<NodeInfo> pre_added;
		pre_added.push({1, 0, (int)real_container_.size() >> 1});

		int64_t min{inf_};
		while (!pre_added.empty())
		{
			NodeInfo added{pre_added.top()};
			pre_added.pop();

			if (added[2] <= left || right <= added[1]) continue;
			if (left <= added[1] && added[2] <= right)
			{
				lazyEvaluate(added[0]);
				min = std::min(min, real_container_[added[0]]);
			}
			else
			{
				lazyEvaluate(added[0]);
				const int mid{(added[1] + added[2]) >> 1};
				pre_added.push({2 * added[0] + 1, mid, added[2]});
				pre_added.push({2 * added[0], added[1], mid});
			}
		}
		return min;
	}
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここまでコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_F&lang=jp
// この問題ではinf_=(1ll << 31) - 1とする必要がある
int main()
{
	int n, q;
	scanf("%d%d", &n, &q);
	RURMinQ rurmq(n);
	for (int i{}; i < q; i++)
	{
		int com;
		scanf("%d", &com);
		if (com)
		{
			int s, t;
			scanf("%d%d", &s, &t);
			printf("%lld\n", rurmq.get(s, t + 1));
		}
		else
		{
			int s, t, x;
			scanf("%d%d%d", &s, &t, &x);
			rurmq.update(s, t + 1, x);
		}
	}
	return 0;
}