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

	// signが正ならDFT、負ならIDFT(1/N倍はされない)
	template <int sign>
	Vector DFT(const Vector& polynomial) const
	{
		Vector prev(size_), ret(polynomial);
		for (int width{size_ >> 1}; width > 0; width >>= 1)
		{
			std::swap(prev, ret);
			for (int begin{}; begin < width; begin++)
				for (int i{}, power_i{sign > 0? 0: size_}; begin + i < size_; i += width, power_i += sign * width)
					ret[begin + i] = prev[(begin + 2 * i) % size_] + power_[power_i] * prev[(begin + 2 * i + width) % size_];
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

		constexpr Real pi{3.1415926535897932384626433832795028841971};
		power_.resize(size_ + 1);
		for (int i{}; i <= size_; i++)
		{
			power_[i].real(std::cos(2 * pi / size_ * i));
			power_[i].imag(std::sin(2 * pi / size_ * i));
		}
	}

	std::vector<int64_t> operator()() const
	{
		const Vector fourierPolynomial1{DFT<1>(polynomial1_)}, fourierPolynomial2{DFT<1>(polynomial2_)};
		Vector fourierPolynomial(size_);
		for (int i{}; i < size_; i++)
			fourierPolynomial[i] = fourierPolynomial1[i] * fourierPolynomial2[i];
		const Vector convolution{DFT<-1>(fourierPolynomial)};
		std::vector<int64_t> ret(size_);
		for (int i{}; i < size_; i++)
			ret[i] = std::round(convolution[i].real() / size_);
		return std::move(ret);
	}
};