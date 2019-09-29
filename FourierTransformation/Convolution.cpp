#include "Convolution.hpp"

int main()
{
	int N;
	scanf("%d", &N);
	std::vector<int64_t> A(N + 1), B(N + 1);
	for (int i{1}; i <= N; i++)
		scanf("%d%d", &A[i], &B[i]);
	auto convolution{Convolution(A, B)()};
	for (int i{1}; i <= 2 * N; i++)
		printf("%lld\n", convolution[i]);

	return 0;
}