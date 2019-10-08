#include <bits/stdc++.h>
#include "extendedEuclidean.hpp"

/////////////////////////
// Garnerのアルゴリズム //
/////////////////////////

int64_t garner(const std::vector<int64_t>& rests, const std::vector<int64_t>& mods, const int64_t ans_mod)
{
	std::vector<int64_t> coefficient(rests);
	for (int i{}; i < (int)rests.size(); i++)
	{
		int64_t mod_multi{1ll};
		for (int j{}; j < i; j++)
		{
			coefficient[i] = (coefficient[i] + mods[i] - mod_multi * coefficient[j] % mods[i]) % mods[i];
			mod_multi = mod_multi * mods[j] % mods[i];
		}
		for (int j{}; j < i; j++)
			coefficient[i] = coefficient[i] * ((extendedEuclidean(mods[j], mods[i])[0] + mods[i]) % mods[i]) % mods[i];
	}
	int64_t ret{}, mod_multi{1ll};
	for (int i{}; i < (int)rests.size(); i++)
	{
		ret = (ret + mod_multi * coefficient[i] % ans_mod) % ans_mod;
		mod_multi = mod_multi * mods[i] % ans_mod;
	}
	return ret;
}