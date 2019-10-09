#include <bits/stdc++.h>
#include "../Modulus/ModInt.hpp"

//////////////////////
// NTTによる畳み込み //
/////////////////////

// 素数と原始根の組
// {1'224'736'769, 3}, // 2^24 * 73 + 1,
// {1'053'818'881, 7}, // 2^20 * 3 * 5 * 67 + 1
// {1'051'721'729, 6}, // 2^20 * 17 * 59 + 1
// {1'045'430'273, 3}, // 2^20 * 997 + 1
// {1'012'924'417, 5}, // 2^21 * 3 * 7 * 23 + 1
// {1'007'681'537, 3}, // 2^20 * 31^2 + 1
// {1'004'535'809, 3}, // 2^21 * 479 + 1
// {998'244'353, 3},  // 2^23 * 7 * 17 + 1	<=デフォルト引数
// {985'661'441, 3},  // 2^22 * 5 * 47 + 1
// {976'224'257, 3},  // 2^20 * 7^2 * 19 + 1
// {975'175'681, 17}, // 2^21 * 3 * 5 * 31 + 1
// {962'592'769, 7},  // 2^21 * 3^3 * 17 + 1
// {950'009'857, 7},  // 2^21 * 4 * 151 + 1
// {943'718'401, 7},  // 2^22 * 3^2 * 5^2 + 1
// {935'329'793, 3},  // 2^22 * 223 + 1
// {924'844'033, 5},  // 2^21 * 3^2 * 7^2 + 1
// {469'762'049, 3},  // 2^26 * 7 + 1
// {167'772'161, 3},  // 2^25 * 5 + 1

template <typename T = ModInt<998'244'353>, int64_t primitive_root = 3>
class NTTConvolution {
private:
	using Vector = std::vector<T>;

	int order_{1};
	T root_;
	Vector power_;
	Vector polynomial1_, polynomial2_;

	// signが正ならDFT、負ならIDFT(1/N倍はされない)
	template <int sign>
	Vector DFT(const Vector& polynomial) const
	{
		Vector prev(order_), ret(polynomial);
		for (int width{order_ >> 1}; width > 0; width >>= 1)
		{
			std::swap(prev, ret);
			for (int begin{}; begin < width; begin++)
				for (int i{}, power_i{sign > 0? 0: order_}; begin + i < order_; i += width, power_i += sign * width)
					ret[begin + i] = prev[(begin + 2 * i) % order_] + power_[power_i] * prev[(begin + 2 * i + width) % order_];
		}
		return std::move(ret);
	}

public:
	NTTConvolution(const Vector& polynomial1, const Vector& polynomial2)
	{
		order_ = 1;
		while (order_ < (int)polynomial1.size() + (int)polynomial2.size() - 1) order_ <<= 1;
		root_ = T(primitive_root) ^ ((T::mod - 1) / order_);

		polynomial1_.resize(order_);
		polynomial2_.resize(order_);

		power_.resize(order_ + 1);
		power_.front() = T(1ll);
		for (int i{1}; i <= order_; i++)
			power_[i] = power_[i - 1] * root_;
		
		std::copy(polynomial1.begin(), polynomial1.end(), polynomial1_.begin());
		std::copy(polynomial2.begin(), polynomial2.end(), polynomial2_.begin());
	}

	Vector operator()() const
	{
		const Vector fourierPolynomial1{DFT<1>(polynomial1_)}, fourierPolynomial2{DFT<1>(polynomial2_)};
		Vector fourierPolynomial(order_);
		for (int i{}; i < order_; i++)
			fourierPolynomial[i] = fourierPolynomial1[i] * fourierPolynomial2[i];
		Vector ret{DFT<-1>(fourierPolynomial)};
		const T order_inv{T(1) / T(order_)};
		for (auto& e: ret)
			e *= order_inv;
		return std::move(ret);
	}
};