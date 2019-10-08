#include "NTTConvolution.hpp"

int main()
{
	int N;
	scanf("%d", &N);
	using Mint998 = ModInt<998'244'353>;
	std::vector<Mint998> A(N + 1), B(N + 1);
	for (int i{1}; i <= N; i++)
	{
		int tmp_a, tmp_b;
		scanf("%d%d", &tmp_a, &tmp_b);
		A[i] = Mint998(tmp_a);
		B[i] = Mint998(tmp_b);
	}
	auto convolution{NTTConvolution<Mint998, 15311432, 23>(A, B)()};
	for (int i{1}; i <= 2 * N; i++)
		std::cout << convolution[i] << std::endl;
	// using Mint998 = ModInt<998'244'353>;
	// Mint998 root{1};
	// for (int i{}; i < 7 * 17; i++)
	// 	root *= Mint998(3);
	// std::cout << root << std::endl;
	// Mint998 pow{root};
	// for (int i{1};; i++, pow *= root)
	// {
	// 	if (pow == Mint(1))
	// 	{
	// 		std::cout << 1 << ' ' << i << std::endl;
	// 		break;
	// 	}
	// 	else if (pow == Mint(0))
	// 	{
	// 		std::cout << 0 << ' ' << i << std::endl;
	// 		break;
	// 	}
	// }

	return 0;
}