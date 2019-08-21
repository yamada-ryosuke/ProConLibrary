#include <bits/stdc++.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////
// 2進数体の行列のランク //
/////////////////////////

// M×N型行列
template<int M, int N>
class Mod2MatrixElimination {
private:
	using Matrix = std::array<std::bitset<N>, M>;

	bool keyExist(const int key_r, const int key_c)
	{
		for (int r_i{key_r}; r_i < M; r_i++)
			if ((*this)[r_i][key_c])
			{
				std::swap(accessIndex_[key_r], accessIndex_[r_i]);
				return true;
			}
		return false;
	}
	Matrix matrix_;
	std::array<int, M> accessIndex_;
	int rank_;

public:
	const int& rank;

	Mod2MatrixElimination(const Matrix& matrix)
		: matrix_(matrix), rank(rank_)
	{
		for (int i{}; i < M; i++) accessIndex_[i] = i;
		int key_r{};
		for (int key_c{}; key_r < M && key_c < N; key_r++, key_c++)
		{
			while (key_c < N && !keyExist(key_r, key_c))
				key_c++;
			if (key_c == N) break;
			for (int r_i{}; r_i < M; r_i++)
				if (r_i != key_r && (*this)[r_i][key_c])
					(*this)[r_i] ^= (*this)[key_r];
		}
		rank_ = key_r;
	}

	typename decltype(matrix_)::reference operator[](const int r) { return matrix_[accessIndex_[r]]; }
};