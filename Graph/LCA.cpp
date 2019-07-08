#include <bits/stdc++.h>

struct Edge {
	int to;
	// int64_t dist{1};

	// int64_t cost;
	// int from;
	// int rev_i;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////
// 最近共通祖先クエリ //
//////////////////////

// コンストラクタに渡す木は子に向かう有向グラフでも無向グラフでもいい
class LCA {
private:
	using ve = std::vector<Edge>;
	using vve = std::vector<ve>;
	using vi = std::vector<int>;
	using vvi = std::vector<vi>;

	const vve& edges_;
	vvi ancestors_;
	vi depthList_;
	const int root_;

	void initDFS(const int index, const int parent, const int depth)
	{
		ancestors_[index].front() = parent;
		depthList_[index] = depth;
		for (auto& e: edges_[index])
			if (e.to != parent)
				initDFS(e.to, index, depth + 1);
	}
	
public:
	const vi& depthList;

	LCA(const vve& adjacentList, const int root)
		: edges_(adjacentList), root_(root), depthList(depthList_)
	{
		int size{1};
		while (1 << (size - 1) <= (int)edges_.size()) size++;
		ancestors_.resize(edges_.size(), vi(size));
		depthList_.resize(edges_.size());
		initDFS(root_, root_, 0);
		for (int i{1}; i < size; i++)
			for (auto& e: ancestors_)
				e[i] = ancestors_[e[i - 1]][i - 1];
	}

	int calcAncestor(const int from, const int distance)
	{
		int ret{from};
		for (int digit{}, rest{distance}; rest > 0; rest >>= 1, digit++)
			if (rest & 1)
				ret = ancestors_[ret][digit];
		return ret;
	}

	int calcLCA(int index0, int index1)
	{
		if (depthList_[index0] > depthList_[index1])
			index0 = calcAncestor(index0, depthList_[index0] - depthList_[index1]);
		else
			index1 = calcAncestor(index1, depthList_[index1] - depthList_[index0]);
		if (index0 == index1) return index0;
		
		for (int digit{(int)ancestors_.front().size() - 1}; digit >= 0; digit--)
			if (ancestors_[index0][digit] != ancestors_[index1][digit])
			{
				index0 = ancestors_[index0][digit];
				index1 = ancestors_[index1][digit];
			}
		return ancestors_[index0][0];
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここまでコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	int n;
	scanf("%d", &n);
	using ve = std::vector<Edge>;
	using vve = std::vector<ve>;
	vve graph(n);
	for (auto& e: graph)
	{
		int k;
		scanf("%d", &k);
		e.resize(k);
		for (auto& f: e)
			scanf("%d", &f.to);
	}
	LCA lca(graph, 0);
	int q;
	scanf("%d", &q);
	for (int i{}; i < q; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		printf("%d\n", lca.calcLCA(u, v));
	}
	return 0;
}