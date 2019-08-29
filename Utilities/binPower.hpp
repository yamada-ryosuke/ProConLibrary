#include <bits/stdc++.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename Monoid>
Monoid binPower(const Monoid& radix, const int64_t exponent, const Monoid& identity)
{
	Monoid ret(identity), pow(radix);
	for (int64_t i{exponent}; i > 0; i >>= 1, pow = pow * pow)
		if (i & 1)
			ret *= pow;
	return std::move(ret);
}