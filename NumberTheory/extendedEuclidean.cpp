#include "extendedEuclidean.hpp"

int main()
{
	int64_t a, b;
	scanf("%lld%lld", &a, &b);
	auto ext{extendedEuclidean(a, b)};

	int64_t min[2]{ext[0], ext[1]};
	while (std::abs(min[0] + b / ext[2]) + std::abs(min[1] - a / ext[2]) < std::abs(min[0]) + std::abs(min[1]))
	{
		min[0] += b / ext[2];
		min[1] -= a / ext[2];
	}
	while (std::abs(min[0] - b / ext[2]) + std::abs(min[1] + a / ext[2]) <= std::abs(min[0]) + std::abs(min[1]))
	{
		min[0] -= b / ext[2];
		min[1] += a / ext[2];
	}

	std::cout << min[0] << ' ' << min[1] << std::endl;

	return 0;
}