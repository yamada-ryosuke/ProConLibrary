#include <bits/stdc++.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////
// Range Add Range Sum Query //
///////////////////////////////

template<typename T = int64_t>
class RAddRSumQ {
private:
	// ノードの番号、左端、右端
	using NodeInfo = std::array<int, 3>;

	std::vector<T> added_container_, sum_container_;

	void build(const unsigned int array_size)
	{
		unsigned int length{1};
		while (length < array_size)
			length <<= 1;
		added_container_.resize(2 * length);
		sum_container_.resize(2 * length);
	}
	// 二つの半開区間[left1,right1)と[left2,right2)の重複する区間の要素数を求める
	int overlapRange(const int left1, const int right1, const int left2, const int right2) const
	{
		return std::max(0, std::min(right1, right2) - std::max(left1, left2));
	}
	// nodeの子ノードをpre_addedにpushする
	void pushNext(std::stack<NodeInfo> &pre_added, const NodeInfo &node)
	{
		const int mid{(node[1] + node[2]) >> 1};
		pre_added.push({2 * node[0] + 1, node[1], mid});
		pre_added.push({2 * node[0], mid, node[2]});
	}

public:
	RAddRSumQ(const unsigned int array_size) { build(array_size); }
	RAddRSumQ(const std::vector<T> &array)
	{
		build(array.size());
		std::copy(array.begin(), array.end(), added_container_.begin() + (added_container_.size() >> 1));
		std::copy(array.begin(), array.end(), sum_container_.begin() + (sum_container_.size() >> 1));

		for (auto i{(sum_container_.size() >> 1) - 1}; i > 0; i--)
			sum_container_[i] = std::min(sum_container_[2 * i], sum_container_[2 * i + 1]);
	}
	// [left,right)の半開区間(0-indexed)にaddedを加算
	void update(const int left, const int right, const T added)
	{
		std::stack<NodeInfo> pre_added;
		pre_added.push({1, 0, (int)sum_container_.size() >> 1});

		while (!pre_added.empty())
		{
			NodeInfo node{pre_added.top()};
			pre_added.pop();
			const int add_range{overlapRange(node[1], node[2], left, right)};
			if (add_range == 0) continue;

			sum_container_[node[0]] += add_range * added;
			if (add_range == node[2] - node[1])
				added_container_[node[0]] += added;
			else
				pushNext(pre_added, node);
		}
	}
	// left,rightは0-indexed、[left, right)の半開区間
	T get(const int left, const int right)
	{
		std::stack<NodeInfo> pre_added;
		pre_added.push({1, 0, (int)sum_container_.size() >> 1});

		T sum{};
		while (!pre_added.empty())
		{
			NodeInfo node{pre_added.top()};
			pre_added.pop();
			const int add_range{overlapRange(node[1], node[2], left, right)};
			if (add_range == 0) continue;

			if (add_range == node[2] - node[1])
				sum += sum_container_[node[0]];
			else
			{
				sum += add_range * added_container_[node[0]];
				pushNext(pre_added, node);
			}
		}
		return sum;
	}
};