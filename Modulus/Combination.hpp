#include "ModInt.hpp"

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