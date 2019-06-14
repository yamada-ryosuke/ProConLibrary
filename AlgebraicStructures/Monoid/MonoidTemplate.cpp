#include <bits/stdc++.h>

class Monoid {
private:
	using BaseValue = int64_t;

	BaseValue value_;

public:
	constexpr Monoid(BaseValue value)
		: value_(value){}
	constexpr Monoid operator+(const Monoid& monoid) const
	{
		BaseValue tmp{value_ + monoid.value_};
		return Monoid(tmp);
	}
	constexpr Monoid getIdentity() const
	{
		BaseValue tmp{};
		return Monoid(tmp);
	}
};