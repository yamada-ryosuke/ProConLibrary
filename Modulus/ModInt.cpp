#include "ModInt.hpp"

int main()
{
	constexpr ModInt<> a(400'000), b(500'000);
	printf("%lld\n", (int64_t)(a * b));

	constexpr ModInt<> c(1);
	printf("%lld\n", (int64_t)(c / 3ll));
	
	ModInt<> d(400'000);
	d *= 500'000;
	printf("%lld\n", (int64_t)d);
	++d;	// 後置は定義されていない
	printf("%lld\n", (int64_t)d);
	std::cout << -d << std::endl;
	
	return 0;
}