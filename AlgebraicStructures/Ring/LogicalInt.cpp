#include <bits/stdc++.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////
// int64_tのxorとandによる環 //
//////////////////////////////

class LogicalInt {
private:
	using BaseValue = int64_t;
	BaseValue value_;

public:
	constexpr LogicalInt(const BaseValue value = 0ll) : value_(value){}
	constexpr LogicalInt operator+(const LogicalInt& operand) const { return LogicalInt(this->value_ ^ operand.value_); }
	constexpr LogicalInt operator-(const LogicalInt& operand) const { return LogicalInt(this->value_ ^ operand.value_); }
	constexpr LogicalInt operator*(const LogicalInt& operand) const { return LogicalInt(this->value_ & operand.value_); }
	
	constexpr LogicalInt& operator=(const LogicalInt& operand)
	{
		this->value_ = operand.value_;
		return *this;
	}
	constexpr LogicalInt& operator=(const BaseValue& operand)
	{
		this->value_ = operand;
		return *this;
	}
	constexpr LogicalInt& operator+=(const LogicalInt& operand)
	{
		*this = *this + operand;
		return *this;
	}
	constexpr LogicalInt& operator-=(const LogicalInt& operand)
	{
		*this = *this - operand;
		return *this;
	}
	constexpr LogicalInt& operator*=(const LogicalInt& operand)
	{
		*this = *this * operand;
		return *this;
	}

	operator BaseValue() { return this->value_; }

	constexpr LogicalInt getZero() const
	{
		return LogicalInt(0ll);
	}
	constexpr LogicalInt getOne() const
	{
		return LogicalInt(-1ll);
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここまでコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// https://atcoder.jp/contests/abc009/tasks/abc009_4

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

int main()
{
	int K;
	int64_t M;
	scanf("%d%lld", &K, &M);
	
	std::vector<LogicalInt> A(K), C(K);
	for (auto& e: A)
	{
		int64_t tmp;
		scanf("%lld", &tmp);
		e = tmp;
	}
	for (auto& e: C)
	{
		int64_t tmp;
		scanf("%lld", &tmp);
		e = tmp;
	}
	std::reverse(C.begin(), C.end());
 
	if (M <= K)
	{
		printf("%lld\n", (int64_t)A[M - 1]);
		return 0;
	}
 
	Matrix<LogicalInt> mat(K, K);
	mat[K - 1] = C;
	for (int i{1}; i < K; i++) mat[i - 1][i] = -1ll;
	printf("%lld\n", (int64_t)((mat ^ (M - K)) * A).back());
	
	return 0;
}