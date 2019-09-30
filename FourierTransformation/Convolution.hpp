#include <bits/stdc++.h>

//////////////
// 畳み込み //
/////////////

class Convolution {
private:
	using Real = long double;	// doubleの方が大幅に速い
	using Complex = std::complex<Real>;
	using Vector = std::vector<Complex>;

	int size_{1};
	Vector power_;
	Vector polynomial1_, polynomial2_;

	// signが正ならDFT、負ならIDFT
	// TODO: 非再帰
	template <int sign>
	Vector DFT(const Vector& polynomial, const int begin, const int width) const
	{
		const int length{size_ / width};
		if (length == 1) return {polynomial[begin]};
		
		const Vector smallFourier1{DFT<sign>(polynomial, begin, 2 * width)}, smallFourier2{DFT<sign>(polynomial, begin + width, 2 * width)};
		Vector ret(length);
		int power_i{sign > 0? 0: size_};
		for (int i{}; 2 * i < length; i++, power_i += sign * width)
			ret[i] = smallFourier1[i] + power_[power_i] * smallFourier2[i];
		for (int i{}; 2 * i < length; i++, power_i += sign * width)
			ret[length / 2 + i] = smallFourier1[i] + power_[power_i] * smallFourier2[i];
		return std::move(ret);
	}

public:
	Convolution(const std::vector<int64_t>& polynomial1, const std::vector<int64_t>& polynomial2)
	{
		while (size_ < (int)polynomial1.size() + (int)polynomial2.size() - 1) size_ <<= 1;

		polynomial1_.resize(size_);
		polynomial2_.resize(size_);

		for (int i{}; i < (int)polynomial1.size(); i++)
			polynomial1_[i].real(polynomial1[i]);
		for (int i{}; i < (int)polynomial2.size(); i++)
			polynomial2_[i].real(polynomial2[i]);

		constexpr Real pi{3.1415926535897932384626433832795028841971};
		power_.resize(size_ + 1);
		power_.front().real(1);
		const Complex root{std::cos(2 * pi / size_), std::sin(2 * pi / size_)};
		for (int i{1}; i <= size_; i++)
			power_[i] = root * power_[i - 1];
	}

	std::vector<int64_t> operator()() const
	{
		const Vector fourierPolynomial1{DFT<1>(polynomial1_, 0, 1)}, fourierPolynomial2{DFT<1>(polynomial2_, 0, 1)};
		Vector fourierPolynomial(size_);
		for (int i{}; i < size_; i++)
			fourierPolynomial[i] = fourierPolynomial1[i] * fourierPolynomial2[i];
		const Vector convolution{DFT<-1>(fourierPolynomial, 0, 1)};
		std::vector<int64_t> ret(size_);
		for (int i{}; i < size_; i++)
			ret[i] = std::round(convolution[i].real() / size_);
		return std::move(ret);
	}
};