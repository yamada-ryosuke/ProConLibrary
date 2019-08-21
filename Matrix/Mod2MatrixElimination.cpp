#include "Mod2MatrixElimination.hpp"

// https://atcoder.jp/contests/abc128/tasks/abc128_c
int main()
{
	int N, M;
	scanf("%d%d", &N, &M);
	std::array<std::bitset<11>, 10> matrix;
	for (int i{}; i < M; i++)
	{
		int k;
		scanf("%d", &k);
		for (int j{}; j < k; j++)
		{
			int s;
			scanf("%d", &s);
			s--;
			matrix[i][s] = true;
		}
	}
	for (int i{}; i < M; i++)
	{
		int p;
		scanf("%d", &p);
		matrix[i][N] = p == 1;
	}
	Mod2MatrixElimination<10, 11> gauss(matrix);
	bool incons{gauss.rank > 0 && gauss[gauss.rank - 1][N]};
	if (incons)
	{
		for (int i{}; i < N; i++)
			if (gauss[gauss.rank - 1][i])
				incons = false;
	}
	if (incons)
		puts("0");
	else
	{
		int ans{1};
		for (int i{}; i < N - gauss.rank; i++) ans *= 2;
		printf("%d\n", ans);
	}
	return 0;
}