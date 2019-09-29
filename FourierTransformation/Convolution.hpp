#include <bits/stdc++.h>

class Convolution {
private:
	using Real = long double;
	using Complex = std::complex<Real>;
	using Vector = std::vector<Complex>;

	Vector polynomial1_, polynomial2_;
	int size_{1};

	Vector DFT(const Vector& polynomial, const int begin, const int width, const int sign)
	{
		const int length{size_ / width};
		if (length == 1) return {polynomial[begin]};
		
		constexpr long double pi{3.1415926535897932384626433832795028841971};
		Vector smallFourier1{DFT(polynomial, begin, 2 * width, sign)}, smallFourier2{DFT(polynomial, begin + width, 2 * width, sign)};
		Vector ret(length);
		const Complex root{std::cos(2 * pi / length * sign), std::sin(2 * pi / length * sign)};
		Complex power{1, 0};
		for (int i{}; 2 * i < length; i++)
		{
			ret[i] = smallFourier1[i] + power * smallFourier2[i];
			power *= root;
		}
		for (int i{}; 2 * i < length; i++)
		{
			ret[length / 2 + i] = smallFourier1[i] + power * smallFourier2[i];
			power *= root;
		}
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
	}

	std::vector<int64_t> operator()()
	{
		Vector fourierPolynomial1{DFT(polynomial1_, 0, 1, 1)}, fourierPolynomial2{DFT(polynomial2_, 0, 1, 1)};
		Vector fourierPolynomial(size_);
		for (int i{}; i < size_; i++)
			fourierPolynomial[i] = fourierPolynomial1[i] * fourierPolynomial2[i];
		Vector convolution{DFT(fourierPolynomial, 0, 1, -1)};
		std::vector<int64_t> ret(size_);
		for (int i{}; i < size_; i++)
			ret[i] = std::round(convolution[i].real() / size_);
		return std::move(ret);
	}
};