#include "extendedEuclidean.hpp"

// https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_E
int main()
{
	int64_t a, b;
	scanf("%lld%lld", &a, &b);
	auto ext{extendedEuclidean(a, b)};
	// 条件を満たすことの証明はコーナーケースを除いてext[0] <= b / 2, ext[1] <= a / 2であることから帰納的になされる
	// https://teratail.com/questions/176282
	std::cout << ext[0] << ' ' << ext[1] << std::endl;

	return 0;
}