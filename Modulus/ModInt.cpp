#include <bits/stdc++.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////
// ModInt //
////////////

// 四則演算の最も左に存在する値がModIntでなければキャストでバグる
// 例えばx = mint * 1000;やx = ModInt(1000) * mint;はいいがx = 1000 * mint;は駄目。
template<int64_t mod_ = 1'000'000'007>
class ModInt {
private:
	int64_t integer_;

public:
	constexpr ModInt(const int64_t initial_number = 0)
		: integer_(initial_number){}
	
	// 四則演算
	constexpr ModInt operator+(const ModInt& operand) const
	{
		ModInt ret{this->integer_ + operand.integer_};
		if (ret.integer_ >= mod_)
			ret.integer_ -= mod_;
		return ret;
	}
	constexpr ModInt operator-(const ModInt& operand) const
	{
		ModInt ret{this->integer_ - operand.integer_};
		if (ret.integer_ < 0)
			ret.integer_ += mod_;
		return ret;
	}
	constexpr ModInt operator*(const ModInt& operand) const
	{
		return {this->integer_ * operand.integer_ % mod_};
	}
	constexpr ModInt operator/(const ModInt& operand) const
	{
		return *this * (operand ^ (mod_ - 2));
	}

	// 累乗
	constexpr ModInt operator^(const int64_t operand) const
	{
		ModInt ret{1}, pow_ope{this->integer_};
		for (int64_t pow{operand}; pow > 0; pow >>= 1)
		{
			if (pow & 1) ret *= pow_ope;
			pow_ope *= pow_ope;
		}
		return ret;
	}

	// 代入
	constexpr ModInt& operator=(const ModInt& operand)
	{
		this->integer_ = operand.integer_;
		return *this;
	}
	constexpr ModInt& operator+=(const ModInt& operand)
	{
		*this = *this + operand;
		return *this;
	}
	constexpr ModInt& operator-=(const ModInt& operand)
	{
		*this = *this - operand;
		return *this;
	}
	constexpr ModInt& operator*=(const ModInt& operand)
	{
		*this = *this * operand;
		return *this;
	}
	constexpr ModInt& operator/=(const ModInt& operand)
	{
		*this = *this / operand;
		return *this;
	}

	// その他
	constexpr operator int64_t() { return integer_; }

	constexpr ModInt getOne() const
	{
		return ModInt(1ll);
	}
	constexpr ModInt getZero() const
	{
		return ModInt(0ll);
	}
};
using Mint = ModInt<>;


//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここまでコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	constexpr ModInt<> a(400'000), b(500'000);
	printf("%lld\n", (int64_t)(a * b));

	constexpr ModInt<> c(1);
	printf("%lld\n", (int64_t)(c / 3ll));
	
	ModInt<> d(400'000);
	d *= 500'000;
	printf("%lld\n", (int64_t)d);
	return 0;
}