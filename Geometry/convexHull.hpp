#include <bits/stdc++.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////
// 凸包 //
//////////

// pointsはソートされる
// 左->下->右->上->左
std::vector<std::complex<long double>> convexHull(std::vector<std::complex<long double>>& points)
{
	constexpr long double epsilon{1e-7};
	std::sort(points.begin(), points.end(),
		[](const auto& a, const auto& b)
		{
			if (std::abs(a.real() - b.real()) >= epsilon) return a.real() < b.real();
			else return a.imag() < b.imag();
		}
	);

	std::vector<std::complex<long double>> ch;
	for (int i{}; i < (int)points.size(); i++)
	{
		while (ch.size() >= 2 && ((points[i] - ch.back()) / (ch[ch.size() - 2] - ch.back())).imag() >= epsilon)
			ch.pop_back();
		ch.push_back(points[i]);
	}
	int rightmost{(int)ch.size()};
	for (int i{(int)points.size() - 2}; i >= 0; i--)
	{
		while (ch.size() >= rightmost + 1 && ((points[i] - ch.back()) / (ch[ch.size() - 2] - ch.back())).imag() >= epsilon)
			ch.pop_back();
		ch.push_back(points[i]);
	}
	return std::move(ch);
}