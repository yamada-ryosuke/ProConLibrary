#include <bits/stdc++.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////
// 部分列オートマトン //
//////////////////////

// 文字列の連続とは限らない部分列を重複なく列挙するオートマトンを行列の形式で作成する
// ret[i][j]=kはi番目の文字のあとに文字'a'+jがくる場合kに遷移することを意味する
// ただしインデックスは引数の文字列の前後に番兵を置いた文字列S'と一致している
// 例えばS="abcbca"ならば
// S' = $ a b c b c a $
// ret= 1 6 6 6 6 6 7 7
//      2 2 4 4 7 7 7 7
//      3 3 3 5 5 7 7 7
// となる(ここではabcの3文字のみで考えたが、実際は26文字のものが作成される)

std::vector<std::array<int, 26>> subsequenceAutomaton(const std::string& S, const char initial_char = 'a')
{
	std::vector<std::array<int, 26>> table(S.size() + 2);
	std::fill(table.back().begin(), table.back().end(), (int)table.size() - 1);
	table[table.size() - 2] = table.back();

	for (int s_i{(int)S.size() - 1}; s_i >= 0; s_i--)
	{
		std::copy(table[s_i + 1].begin(), table[s_i + 1].end(), table[s_i].begin());
		table[s_i][S[s_i] - initial_char] = s_i + 1;
	}
	return std::move(table);
}