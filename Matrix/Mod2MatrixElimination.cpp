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

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここまでコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// https://atcoder.jp/contests/abc128/tasks/abc128_c
int main()
{
	int N, M;
	scanf("%d%d", &N, &M);
	std::array<std::bitset<11>, 10> matrix;
	for (int i{}; i < M; i++)
	{
		int k;
		scanf("%d", &k);
		for (int j{}; j < k; j++)
		{
			int s;
			scanf("%d", &s);
			s--;
			matrix[i][s] = true;
		}
	}
	for (int i{}; i < M; i++)
	{
		int p;
		scanf("%d", &p);
		matrix[i][N] = p == 1;
	}
	Mod2MatrixElimination<10, 11> gauss(matrix);
	bool incons{gauss.rank > 0 && gauss[gauss.rank - 1][N]};
	if (incons)
	{
		for (int i{}; i < N; i++)
			if (gauss[gauss.rank - 1][i])
				incons = false;
	}
	if (incons)
		puts("0");
	else
	{
		int ans{1};
		for (int i{}; i < N - gauss.rank; i++) ans *= 2;
		printf("%d\n", ans);
	}
	return 0;
}