#include <bits/stdc++.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////
// 行列型 //
///////////

// 加算、減算、乗算をもつN*M型行列
// N=Mで環をつくる
template<typename T = int64_t>
class Matrix {
private:
	using RowVector = std::vector<T>;

	std::vector<RowVector> container_;

public:
	const int N, M;

	Matrix(const int row_size, const int column_size)
		: N(row_size), M(column_size), container_(row_size, RowVector(column_size)){}
	Matrix(Matrix<T>&& mat)
		: N(mat.N), M(mat.M), container_(std::move(mat.container_)){}
	Matrix(Matrix<T>& mat)
		: N(mat.N), M(mat.M), container_(mat.container_){}

	// 要素アクセス
	RowVector& operator[](const int r) { return container_[r]; }
	const RowVector& operator[](const int r) const { return container_[r]; }
	// イテレータ
	typename decltype(container_)::iterator begin(){ return container_.begin(); }
	typename decltype(container_)::iterator end(){ return container_.end(); }

	// 環の演算
	Matrix<T> operator+(const Matrix<T>& mat) const
	{
		Matrix<T> ret{*this};
		for (int r_i{}; r_i < N; r_i++)
			for (int c_i{}; c_i < M; c_i++)
				ret[r_i][c_i] += mat[r_i][c_i];
		return std::move(ret);
	}
	Matrix<T> operator-(const Matrix<T>& mat) const
	{
		Matrix<T> ret{*this};
		for (int r_i{}; r_i < N; r_i++)
			for (int c_i{}; c_i < M; c_i++)
				ret[r_i][c_i] -= mat[r_i][c_i];
		return std::move(ret);
	}
	Matrix<T> operator*(const Matrix<T>& mat) const
	{
		Matrix<T> ret(this->N, mat.M);
		for (int r_i{}; r_i < this->N; r_i++)
			for (int c_i{}; c_i < mat.M; c_i++)
				for (int l_i{}; l_i < this->M; l_i++)
					ret[r_i][c_i] += (*this)[r_i][l_i] * mat[l_i][c_i];
		return std::move(ret);
	}
	std::vector<T> operator*(const std::vector<T>& vec) const
	{
		std::vector<T> ret(N);
		for (int r_i{}; r_i < N; r_i++)
			for (int c_i{}; c_i < M; c_i++)
				ret[r_i] += (*this)[r_i][c_i] * vec[c_i];
		return std::move(ret);
	}

	// 代入演算子
	Matrix<T>& operator+=(const Matrix& mat)
	{
		*this = *this + mat;
		return *this;
	}
	Matrix<T>& operator-=(const Matrix& mat)
	{
		*this = *this - mat;
		return *this;
	}
	Matrix<T>& operator*=(const Matrix& mat)
	{
		*this = *this * mat;
		return *this;
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここまでコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3035
int main()
{
	int n, m, l;
	scanf("%d%d%d", &n, &m, &l);
	Matrix<> A(n, m), B(m, l);
	for (auto& e: A)
		for (auto& f: e)
			scanf("%lld", &f);
	for (auto& e: B)
		for (auto& f: e)
			scanf("%lld", &f);
	Matrix<> C(A * B);
	for (int i{}; i < n; i++)
		for (int j{}; j < l; j++)
			printf("%lld%c", C[i][j], j == l - 1? '\n': ' ');
	return 0;
}