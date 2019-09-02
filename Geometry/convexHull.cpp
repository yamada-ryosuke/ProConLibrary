#include "convexHull.hpp"

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_A&lang=jp
int main()
{
	constexpr long double epsilon{1e-7};
	int n;
	scanf("%d", &n);
	std::vector<std::complex<long double>> points(n);
	for (auto& e: points)
	{
		long double x, y;
		scanf("%Lf%Lf", &x, &y);
		e.real(x);
		e.imag(y);
	}
	auto ch{convexHull(points)};
	if (std::abs(ch.front() - ch.back()) < epsilon) ch.pop_back();

	int begin{};
	for (int i{}; i < (int)ch.size(); i++)
		if (ch[i].imag() < ch[begin].imag() - epsilon)
			begin = i;

	printf("%d\n", ch.size());
	for (int i{}; i < (int)ch.size(); i++)
		printf("%d %d\n", (int)std::round(ch[(begin + i) % ch.size()].real()), (int)std::round(ch[(begin + i) % ch.size()].imag()));

	return 0;
}