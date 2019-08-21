#include "Matrix.hpp"

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_7_D&lang=jp
int main()
{
	int n, m, l;
	scanf("%d%d%d", &n, &m, &l);
	Matrix<> A(n, m), B(m, l);
	for (auto& e: A)
		for (auto& f: e)
			scanf("%lld", &f);
	for (auto& e: B)
		for (auto& f: e)
			scanf("%lld", &f);
	Matrix<> C(A * B);
	for (int i{}; i < n; i++)
		for (int j{}; j < l; j++)
			printf("%lld%c", C[i][j], j == l - 1? '\n': ' ');
	return 0;
}