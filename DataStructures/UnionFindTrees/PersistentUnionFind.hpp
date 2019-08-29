#include <bits/stdc++.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////
// 永続Union-Find木 //
/////////////////////

// 0-indexed
class PersistentUnionFind {
private:
	std::vector<int> parent_, size_, time_;
	int counter_{-1};

public:
	PersistentUnionFind(const int size)
		:parent_(size, -1), size_(size, 1), time_(size, -1) {}

	int calcRoot(const int index, const int time) const
	{
		const int &parent{parent_[index]};
		if (parent == -1 || time_[index] > time) return index;
		else return calcRoot(parent, time);
	}

	bool areConnected(const int index1, const int index2, const int time) const
	{
		return calcRoot(index1, time) == calcRoot(index2, time);
	}

	void unite(const int index1, const int index2)
	{
		counter_++;
		const int root1{calcRoot(index1, counter_)}, root2{calcRoot(index2, counter_)};
		if (root1 == root2) return;
		if (size_[root1] <= size_[root2])
		{
			size_[root2] += size_[root1];
			parent_[root1] = root2;
			time_[root1] = counter_;
		}
		else
		{
			size_[root1] += size_[root2];
			parent_[root2] = root1;
			time_[root2] = counter_;
		}
		return;
	}

	int calcSize(const int index)
	{
		return size_[calcRoot(index, counter_)];
	}

};