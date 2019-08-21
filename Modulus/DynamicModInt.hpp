#include <bits/stdc++.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////
// 動的modのModInt //
////////////////////

// 四則演算の最も左に存在する値がModIntでなければキャストでバグる
// 例えばx = mint * 1000;やx = DynamicModInt(1000) * mint;はいいがx = 1000 * mint;は駄目。
int64_t mod{};
class DynamicModInt {
private:
	int64_t integer_;

public:
	DynamicModInt(const int64_t initial_number = 0)
		: integer_(initial_number){}
	
	// 四則演算
	DynamicModInt operator+(const DynamicModInt& operand) const
	{
		DynamicModInt ret{this->integer_ + operand.integer_};
		if (ret.integer_ >= mod)
			ret.integer_ -= mod;
		return ret;
	}
	DynamicModInt operator-(const DynamicModInt& operand) const
	{
		DynamicModInt ret{this->integer_ - operand.integer_};
		if (ret.integer_ < 0)
			ret.integer_ += mod;
		return ret;
	}
	DynamicModInt operator*(const DynamicModInt& operand) const
	{
		return {this->integer_ * operand.integer_ % mod};
	}

	// 累乗
	DynamicModInt operator^(const int64_t operand) const
	{
		DynamicModInt ret{1}, pow_ope{this->integer_};
		for (int64_t pow{operand}; pow > 0; pow >>= 1)
		{
			if (pow & 1) ret *= pow_ope;
			pow_ope *= pow_ope;
		}
		return ret;
	}

	// 代入
	DynamicModInt& operator=(const DynamicModInt& operand)
	{
		this->integer_ = operand.integer_;
		return *this;
	}
	DynamicModInt& operator+=(const DynamicModInt& operand)
	{
		*this = *this + operand;
		return *this;
	}
	DynamicModInt& operator-=(const DynamicModInt& operand)
	{
		*this = *this - operand;
		return *this;
	}
	DynamicModInt& operator*=(const DynamicModInt& operand)
	{
		*this = *this * operand;
		return *this;
	}

	// その他
	operator int64_t() { return integer_; }

	DynamicModInt getOne() const
	{
		return DynamicModInt(1ll);
	}
	DynamicModInt getZero() const
	{
		return DynamicModInt(0ll);
	}
};
using DMint = DynamicModInt;