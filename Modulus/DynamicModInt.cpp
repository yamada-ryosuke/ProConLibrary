#include "DynamicModInt.hpp"
#include "../Matrix/Matrix.hpp"

// https://atcoder.jp/contests/abc129/tasks/abc129_f
int main()
{
	int64_t L, A, B;
	scanf("%lld%lld%lld%lld", &L, &A, &B, &mod);
	std::vector<int64_t> digit(19, -1);
	int64_t ten_pow{1};
	for (int i{1}; ; i++)
	{
		ten_pow *= 10;
		if (A >= ten_pow) continue;
		digit[i] = (ten_pow - 1 - A) / B;
		if (digit[i] >= L - 1)
		{
			digit[i] = L - 1;
			break;
		}
	}

	std::vector<DMint> sum(19);
	DMint a_mod(A % mod), b_mod(B % mod), ten_pow_mod(1ll);
	for (int i{1}; digit[i - 1] != L - 1; i++)
	{
		ten_pow_mod *= DMint(10);
		if (digit[i] < 0 || digit[i] == digit[i - 1]) continue;
		int64_t num{digit[i] - digit[i - 1]};

		Matrix<DMint> aMat(2, DMint(2));
		aMat[0][0] = ten_pow_mod;
		aMat[0][1] = aMat[1][1] = DMint(1);
		std::vector<DMint> beginA{DMint(0), DMint(1)};
		sum[i] = ((aMat ^ num) * beginA)[0] * (a_mod + (DMint((digit[i - 1] + mod) % mod) + DMint(1ll)) * b_mod);
		
		Matrix<DMint> bMat(4, DMint(4));
		bMat[0][0] = ten_pow_mod;
		bMat[0][1] = bMat[1][1] = bMat[2][0] = bMat[3][1] = bMat[2][2] = bMat[3][3] = DMint(1ll);

		Matrix<DMint> beginB(4, DMint(2));
		beginB[0][0] = beginB[1][1] = DMint(1);
		sum[i] += b_mod * ((bMat ^ num) * beginB * beginA)[2];
	}
	std::vector<DMint> shift(19, DMint(1ll));
	for (int i{17}; i > 0; i--)
	{
		if (digit[i + 1] < 0) continue;
		DMint tmp(1);
		ten_pow_mod = DMint(10);
		for (int64_t j{(digit[i + 1] - digit[i])}; j > 0; j >>= 1, ten_pow_mod *= ten_pow_mod)
			if (j & 1)
				tmp *= ten_pow_mod;
		shift[i] = shift[i + 1];
		for (int64_t j{i + 1}; j > 0; j >>= 1, tmp = tmp * tmp % mod)
			if (j & 1)
				shift[i] *= tmp;
		sum[i] *= shift[i];
	}
	DMint ans{};
	for (int i{1}; i <= 18; i++)
	{
		if (digit[i] < 0 || digit[i] == digit[i - 1]) continue;
		ans += sum[i];
	}
	std::cout << ans << std::endl;

	return 0;
}
