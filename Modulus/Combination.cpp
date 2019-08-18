#include <bits/stdc++.h>

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

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////
// 組み合わせ //
///////////////

template<int64_t mod_ = 1'000'000'007, int max_ = 200'000>
class Combination {
public:
	std::array<ModInt<mod_>, max_ + 1> inv, fact, finv;

	constexpr Combination()
	{
		inv[0] = inv[1] = fact[0] = fact[1] = finv[0] = finv[1] = 1;
		for (int num{2}; num <= max_; num++)
		{
			inv[num] = (mod_ - (int64_t)inv[mod_ % num] * (mod_ / num) % mod_) % mod_;
			fact[num] = num * fact[num - 1] % mod_;
			finv[num] = inv[num] * finv[num - 1] % mod_;
		}
	}

	constexpr ModInt<mod_> getCombi(const int n, const int r) const
	{
		if (r < 0 || n < 0 || n - r < 0) return 0;
		return fact[n] * finv[r] * finv[n - r];
	}

	constexpr ModInt<mod_> getPerm(const int n, const int r) const
	{
		if (r < 0 || n < 0 || n - r < 0) return 0;
		return fact[n] * finv[n - r];
	}
};
Combination<> combi;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここまでコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	for (int i{}; i < 10; i++)
	{
		printf("%lld, %lld, %lld\n", (int64_t)combi.inv[i], (int64_t)combi.fact[i], (int64_t)combi.finv[i]);
	}
	printf("%lld\n", (int64_t)combi.getCombi(5, 3));

	return 0;
}