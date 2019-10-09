#include "NTTConvolution.hpp"

// https://judge.yosupo.jp/problem/convolution_mod
int main()
{
	int N, M;
	scanf("%d%d", &N, &M);
	using Mint998 = ModInt<998'244'353>;
	std::vector<Mint998> A(N), B(M);
	for (auto& e: A)
	{
		int tmp;
		scanf("%d", &tmp);
		e = Mint998(tmp);
	}
	for (auto& e: B)
	{
		int tmp;
		scanf("%d", &tmp);
		e = Mint998(tmp);
	}
	auto convolution{NTTConvolution<Mint998, 3>(A, B)()};
	for (int i{}; i < N + M - 1; i++)
		std::cout << convolution[i] << (i + 1 == N + M? '\n': ' ');

	return 0;
}