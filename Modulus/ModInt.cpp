#include <bits/stdc++.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

template<int64_t mod_ = 1'000'000'007>
class ModInt {
private:
	int64_t integer_;

public:
	ModInt(const int64_t initial_number = 0)
		: integer_(initial_number){}
	
	// 四則演算
	ModInt operator+(const int64_t operand)
	{
		int64_t ret{integer_ + operand};
		if (ret >= mod_)
			ret -= mod_;
		return ModInt(ret);
	}
	ModInt operator-(const int64_t operand)
	{
		int64_t ret{integer_ - operand};
		if (ret < 0)
			ret += mod_;
		return ModInt(ret);
	}
	ModInt operator*(const int64_t operand)
	{
		return ModInt(integer_ * operand % mod_);
	}
	ModInt operator/(const int64_t operand)
	{
		int64_t ret{1}, pow_ope{operand};
		for (int64_t pow_mod{mod_ - 2}; pow_mod > 0; pow_mod >>= 1)
		{
			if (pow_mod & 1)
				ret = ret * pow_ope % mod_;
			pow_ope = pow_ope * pow_ope % mod_;
		}
		return ModInt(ret);
	}

	// 代入
	ModInt& operator=(const int64_t operand)
	{
		integer_ = operand;
		return *this;
	}
	ModInt& operator+=(const int64_t operand)
	{
		*this = *this + operand;
		return *this;
	}
	ModInt& operator-=(const int64_t operand)
	{
		*this = *this - operand;
		return *this;
	}
	ModInt& operator*=(const int64_t operand)
	{
		*this = *this * operand;
		return *this;
	}
	ModInt& operator/=(const int64_t operand)
	{
		*this = *this / operand;
		return *this;
	}

	// その他
	operator int64_t() { return integer_; }
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここまでコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	ModInt<> a(400'000), b(500'000);
	printf("%lld\n", (int64_t)(a * b));

	ModInt<> c(1);
	printf("%lld\n", (int64_t)(c / 3ll));
	
	ModInt<> d(400'000);
	d *= 500'000;
	printf("%lld\n", (int64_t)d);
	return 0;
}