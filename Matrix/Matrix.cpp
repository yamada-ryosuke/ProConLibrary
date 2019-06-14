#include <bits/stdc++.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////
// 行列型 //
///////////

// 加算、減算、乗算をもつM×N型行列
// M=Nで環をつくる
template<typename T = int64_t>
class Matrix {
private:
	using RowVector = std::vector<T>;

	std::vector<RowVector> container_;

public:
	const int M, N;

	Matrix(const int row_size, const int column_size)
		: M(row_size), N(column_size), container_(row_size, RowVector(column_size)){}
	// ムーブコンストラクタ
	Matrix(Matrix&& mat)
		: M(mat.M), N(mat.N), container_(std::move(mat.container_)){}
	// コピーコンストラクタ
	Matrix(Matrix& mat)
		: M(mat.M), N(mat.N), container_(mat.container_){}

	// 要素アクセス
	RowVector& operator[](const int r) { return container_[r]; }
	const RowVector& operator[](const int r) const { return container_[r]; }
	// イテレータ
	typename decltype(container_)::iterator begin(){ return container_.begin(); }
	typename decltype(container_)::iterator end(){ return container_.end(); }

	// 環の演算
	Matrix operator+(const Matrix& mat) const
	{
		Matrix ret{*this};
		for (int r_i{}; r_i < M; r_i++)
			for (int c_i{}; c_i < N; c_i++)
				ret[r_i][c_i] += mat[r_i][c_i];
		return std::move(ret);
	}
	Matrix operator-(const Matrix& mat) const
	{
		Matrix ret{*this};
		for (int r_i{}; r_i < M; r_i++)
			for (int c_i{}; c_i < N; c_i++)
				ret[r_i][c_i] -= mat[r_i][c_i];
		return std::move(ret);
	}
	Matrix operator*(const Matrix& mat) const
	{
		Matrix ret(this->M, mat.N);
		for (int r_i{}; r_i < this->M; r_i++)
			for (int c_i{}; c_i < mat.N; c_i++)
				for (int l_i{}; l_i < this->N; l_i++)
					ret[r_i][c_i] += (*this)[r_i][l_i] * mat[l_i][c_i];
		return std::move(ret);
	}
	std::vector<T> operator*(const std::vector<T>& vec) const
	{
		std::vector<T> ret(M);
		for (int r_i{}; r_i < M; r_i++)
			for (int c_i{}; c_i < N; c_i++)
				ret[r_i] += (*this)[r_i][c_i] * vec[c_i];
		return std::move(ret);
	}

	// 累乗
	Matrix operator^(const int64_t index)
	{
		Matrix ret((*this).getOne()), pow(*this);
		for (int64_t i{index}; i > 0; i >>= 1)
		{
			if (i & 1)
				ret *= pow;
			pow *= pow;
		}
		return std::move(ret);
	}

	// 代入演算子
	Matrix& operator=(const Matrix& mat)
	{
		this->container_ = mat.container_;
		return *this;
	}	
	Matrix& operator+=(const Matrix& mat)
	{
		*this = *this + mat;
		return *this;
	}
	Matrix& operator-=(const Matrix& mat)
	{
		*this = *this - mat;
		return *this;
	}
	Matrix& operator*=(const Matrix& mat)
	{
		*this = *this * mat;
		return *this;
	}

	// ゼロ行列と単位行列
	constexpr Matrix getOne() const
	{
		Matrix ret(M, N);
		for (int i{}; i < N; i++)
			ret[i][i] = ret[i][i].getOne();
		return std::move(ret);
	}
	constexpr Matrix getZero() const
	{
		return Matrix(M, N);
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