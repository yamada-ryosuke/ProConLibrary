#include <bits/stdc++.h>

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
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

template<int64_t mod_ = 1'000'000'007>
class Combination {
public:
	std::vector<ModInt<mod_>> inv, fact, finv;

	Combination(const int max = 200'000)
		: inv(max + 1), fact(max + 1), finv(max + 1)
	{
		inv[0] = inv[1] = fact[0] = fact[1] = finv[0] = finv[1] = 1;
		for (int num{2}; num <= max; num++)
		{
			inv[num] = (mod_ - (int64_t)inv[mod_ % num] * (mod_ / num) % mod_) % mod_;
			fact[num] = num * fact[num - 1] % mod_;
			finv[num] = inv[num] * finv[num - 1] % mod_;
		}
	}

	int64_t getCombi(const int n, const int r)
	{
		if (r < 0 || n < 0 || n - r < 0) return 0;
		return fact[n] * finv[r] * finv[n - r];
	}

	int64_t getPerm(const int n, const int r)
	{
		if (r < 0 || n < 0 || n - r < 0) return 0;
		return fact[n] * finv[n - r];
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここまでコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Combination<> combi;
	for (int i{}; i < 10; i++)
	{
		printf("%lld, %lld, %lld\n", (int64_t)combi.inv[i], (int64_t)combi.fact[i], (int64_t)combi.finv[i]);
	}
	printf("%lld\n", (int64_t)combi.getCombi(5, 3));

	return 0;
}