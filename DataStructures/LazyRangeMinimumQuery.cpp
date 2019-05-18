#include <bits/stdc++.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////
// Lazy Range Minimum Query(未完成) //
/////////////////////////////////////

class LazyRangeMinimumQuery {
private:
	std::vector<long long> container_;
	void constructorHelper(const unsigned int array_size)
	{
		unsigned int length{1};
		while (length < array_size)
			length <<= 1;
		container_.resize(2 * length, 1ll << 60);
	}

public:
	LazyRangeMinimumQuery(const unsigned int array_size) { constructorHelper(array_size); }
	LazyRangeMinimumQuery(const std::vector<long long> &array)
	{
		constructorHelper(array.size());
		std::copy(array.begin(), array.end(), container_.begin() + array.size());
		for (unsigned int i{(container_.size() >> 1) - 1}; i > 0; i--)
			container_[i] = std::min(container_[2 * i], container_[2 * i + 1]);
	}
	// left_index,right_indexは0-indexed、[left_index, right_index)の半開区間
	long long update(const int left_index, const int right_index, const int assigned)
	{
		
	}

};


//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここまでコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


// AOJ
int main()
{
	int n, q;
	scanf("%d%d", &n, &q);
	LazyRangeMinimumQuery rmq(n);
	for (int i{}; i < q; i++)
	{
		int com, x, y;
		scanf("%d%d%d", &com, &x, &y);
	}
	return 0;
}