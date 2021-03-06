#include <bits/stdc++.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////
// Range Sum Query (BIT) //
///////////////////////////

class RSumQBIT {
private:
	std::vector<int64_t> container_;

	int64_t getHelper(const int index) const
	{
		if (index < 0) return 0;
		if ((int)(container_.size()) <= index) return container_.back();
		int64_t sum{};
		for (int add_place{index}; add_place > 0; add_place -= add_place & -add_place)
			sum += container_[add_place];
		return sum;
	}

public:
	RSumQBIT(const int array_size)
		: container_(array_size + 1) {}
	// indexは0-indexed
	void update(const int index, const int64_t added)
	{
		for (int update_place{index + 1}; update_place < (int)(container_.size()); update_place += update_place & -update_place)
			container_[update_place] += added;
	}
	// left,rightは0-indexed、[left, right)の半開区間
	int64_t get(const int left, const int right) const
	{
		return -getHelper(left) + getHelper(right);
	}
};