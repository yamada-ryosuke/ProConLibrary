#include "ModInt.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////
// 組み合わせ //
///////////////

template<typename T = Mint, int max_ = 200'000>
class Combination {
public:
	std::array<Mint, max_ + 1> inv, fact, finv;

	constexpr Combination()
	{
		inv[0] = inv[1] = fact[0] = fact[1] = finv[0] = finv[1] = 1;
		for (int num{2}; num <= max_; num++)
		{
			inv[num] = (T::mod - (int64_t)inv[T::mod % num] * (T::mod / num) % T::mod) % T::mod;
			fact[num] = num * fact[num - 1] % T::mod;
			finv[num] = inv[num] * finv[num - 1] % T::mod;
		}
	}

	constexpr Mint getCombi(const int n, const int r) const
	{
		if (r < 0 || n < 0 || n - r < 0) return 0;
		return fact[n] * finv[r] * finv[n - r];
	}

	constexpr Mint getPerm(const int n, const int r) const
	{
		if (r < 0 || n < 0 || n - r < 0) return 0;
		return fact[n] * finv[n - r];
	}
};
Combination<> combi;