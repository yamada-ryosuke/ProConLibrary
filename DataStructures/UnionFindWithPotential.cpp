#include <bits/stdc++.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////
// ポテンシャル付きUnion-Find木(未検証) //
////////////////////////////////////////

// 0-indexed
class UnionFindWithPotential {
private:
	std::vector<int> parent_, size_;
	std::vector<int64_t> potential_delta_;

	// indexの含まれる木の根のノード番号を返す
	int calcRoot(const int index)
	{
		int &parent{parent_[index]};
		if (parent == index) return index;

		const int root{calcRoot(parent)};
		potential_delta_[index] += potential_delta_[parent];
		parent = root;
		return parent;
	}
public:
	UnionFindWithPotential(const int size)
		:parent_(size), size_(size, 1), potential_delta_(size)
	{
		for (int i{}; i < size; i++) parent_[i] = i;
	}

	// index1とindex2の連結判定
	bool areConnected(const int index1, const int index2)
	{
		return calcRoot(index1) == calcRoot(index2);
	}

	// potential(index1) = potential(index2) + weightとなるよう結合
	bool unite(const int index1, const int index2, const int64_t weight)
	{
		const int root1{calcRoot(index1)}, root2{calcRoot(index2)};
		if (root1 == root2)
			return potential_delta_[index1] == potential_delta_[index2] + weight;
		if (size_[root1] <= size_[root2])
		{
			size_[root2] += size_[root1];
			potential_delta_[root1] = (potential_delta_[index2] + weight) - potential_delta_[index1];
			parent_[root1] = root2;
		}
		else
		{
			size_[root1] += size_[root2];
			potential_delta_[root2] = potential_delta_[index1] - (weight + potential_delta_[index2]);
			parent_[root2] = root1;
		}
		return true;
	}

	// indexが含まれる木の要素数を返す
	int calcSize(const int index)
	{
		return size_[calcRoot(index)];
	}

	// potential(index1) - potential(index2)を返す
	// 根が異なる場合はLLONG_MAXを返す
	int64_t calcDiff(const int index1, const int index2)
	{
		if (calcRoot(index1) != calcRoot(index2))
			return LLONG_MAX;
		return potential_delta_[index1] - potential_delta_[index2];
	}
};

bool solve()
{
	int N, M;
	scanf("%d%d", &N, &M);
	UnionFindWithPotential ufp(N);
	for (int i{}; i < M; i++)
	{
		int L, R;
		long long D;
		scanf("%d%d%lld", &L, &R, &D);
		L--; R--;
		if (!ufp.unite(R, L, D)) return false;
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここまでコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// https://atcoder.jp/contests/abc087/tasks/arc090_b
int main()
{
	if (solve()) puts("Yes");
	else puts("No");

	return 0;
}