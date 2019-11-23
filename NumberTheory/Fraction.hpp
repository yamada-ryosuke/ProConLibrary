#include "calcLCM.hpp"

//////////
// 分数 //
//////////

// gcdを求める際にstd::swapを使うため、constexprには出来ない
class Fraction {
private:
	using Integer = int64_t;
	Integer numerator_, denominator_;

	void reduce()
	{
		const Integer gcd{(Integer)calcGCD(std::abs(numer), std::abs(denom))};
		numerator_ /= gcd;
		denominator_ /= gcd;
		if (denom < 0)
		{
			numerator_ *= -1;
			denominator_ *= -1;
		}
	}

public:
	const Integer &numer, &denom;

	Fraction(const Integer& initial_numerator = 0, const Integer& initial_denominator = 1)
		: numerator_(initial_numerator), denominator_(initial_denominator),
		numer(numerator_), denom(denominator_)
		{
			reduce();
		}
	Fraction(const Fraction& fraction)
		: numerator_(fraction.numer), denominator_(fraction.denom),
		numer(numerator_), denom(denominator_) {}
	
	// 四則演算
	Fraction operator+(const Fraction& operand) const
	{
		Fraction ret{1, (Integer)calcLCM(std::abs(this->denom), std::abs(operand.denom))};
		ret.numerator_ = this->numer * (ret.denom / this->denom) + operand.numer * (ret.denom / operand.denom);
		ret.reduce();

		return ret;
	}
	Fraction operator-(const Fraction& operand) const
	{
		Fraction ret{1, (Integer)calcLCM(std::abs(this->denom), std::abs(operand.denom))};
		ret.numerator_ = this->numer * (ret.denom / this->denom) - operand.numer * (ret.denom / operand.denom);
		ret.reduce();

		return ret;
	}
	Fraction operator*(const Fraction& operand) const
	{
		return {this->numer * operand.numer, this->denom * operand.denom};
	}
	Fraction operator*(const Integer& operand) const
	{
		return {this->numer * operand, this->denom};
	}
	Fraction operator/(const Fraction& operand) const
	{
		return {this->numer * operand.denom, this->denom * operand.numer};
	}
	Fraction operator/(const Integer& operand) const
	{
		return {this->numer, this->denom * operand};
	}

	// 代入
	Fraction& operator=(const Fraction& operand)
	{
		this->numerator_ = operand.numer;
		this->denominator_ = operand.denom;
		return *this;
	}
	Fraction& operator+=(const Fraction& operand)
	{
		*this = *this + operand;
		return *this;
	}
	Fraction& operator-=(const Fraction& operand)
	{
		*this = *this - operand;
		return *this;
	}
	Fraction& operator*=(const Fraction& operand)
	{
		*this = *this * operand;
		return *this;
	}
	Fraction& operator/=(const Fraction& operand)
	{
		*this = *this / operand;
		return *this;
	}

	// 比較
	bool operator==(const Fraction& operand) const
	{
		return this->numer * operand.denom == operand.numer * this->denom;
	}
	bool operator<=(const Fraction& operand) const
	{
		return this->numer * operand.denom <= operand.numer * this->denom;
	}
	bool operator>=(const Fraction& operand) const
	{
		return this->numer * operand.denom >= operand.numer * this->denom;
	}
	bool operator!=(const Fraction& operand) const
	{
		return !(*this == operand);
	}
	bool operator<(const Fraction& operand) const
	{
		return !(*this >= operand);
	}
	bool operator>(const Fraction& operand) const
	{
		return !(*this <= operand);
	}

	// その他
	// 逆数
	Fraction inv() const { return Fraction{denom, numer}; }
	// 天井関数
	Integer ceil() const { return (numer + denom - 1) / denom; }
	// 床関数
	Integer floor() const { return numer / denom; }
	// 小数型への変換
	long double real() const { return (long double)numer / denom; }
	// 文字列への変換
	std::string toString() const
	{
		std::string ret{std::to_string(numer)};
		if (denom != 1) ret += std::string("/") + std::to_string(denom);
		return ret;
	}
};