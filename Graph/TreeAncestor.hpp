#include "EdgeTemplate.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////
// 木の祖先クエリ //
///////////////////

// コンストラクタに渡す木は子に向かう有向グラフでも無向グラフでもいい
// Edgeは{to}
class TreeAncestor {
private:
	using vi = std::vector<int>;
	using vvi = std::vector<vi>;

	const EdgeLists& edges_;
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

	TreeAncestor(const EdgeLists& adjacentList, const int root)
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

	// fromからdistanceだけ根の方向にさかのぼった頂点のindexを返す
	int calcAncestor(const int from, const int distance) const
	{
		int ret{from};
		for (int digit{}, rest{distance}; rest > 0; rest >>= 1, digit++)
			if (rest & 1)
				ret = ancestors_[ret][digit];
		return ret;
	}

	// index0とindex1の最近共通祖先のindexを返す
	int calcLCA(int index0, int index1) const
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