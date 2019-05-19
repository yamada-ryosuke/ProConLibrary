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

class SubsequenceAutomaton {
private:
	using Alphabet_t = std::array<int, 26>;
	using Automaton_t = std::vector<Alphabet_t>;

public:
	Automaton_t table;
	
	SubsequenceAutomaton(const std::string& S, const char initial_char = 'a')
		: table(S.size() + 2)
	{
		std::fill(table.back().begin(), table.back().end(), (int)table.size() - 1);
		table[table.size() - 2] = table.back();

		for (int s_i{(int)S.size() - 1}; s_i >= 0; s_i--)
		{
			std::copy(table[s_i + 1].begin(), table[s_i + 1].end(), table[s_i].begin());
			table[s_i][S[s_i] - initial_char] = s_i + 1;
		}
	}
};

class Subsequence {
private:
	std::stack<int> indices_;
	SubsequenceAutomaton automaton_;
	char initial_char_;

	bool add(int next_c)
	{
		for (; next_c < 26; next_c++)
		{
			if (automaton_.table[indices_.top()][next_c] == (int)automaton_.table.size() - 1)
				continue;
			str.push_back('a' + next_c);
			indices_.push(automaton_.table[indices_.top()][next_c]);
			return true;
		}
		return false;
	}

public:
	std::string str;

	Subsequence(std::string& S, const char initial_char = 'a')
		: automaton_(S, initial_char), initial_char_(initial_char)
	{
		indices_.push(0);
	}

	bool next()
	{
		int next_c{};
		while (!add(next_c))
		{
			if (str.empty()) return false;
			next_c = str.back() - initial_char_ + 1;
			str.pop_back();
			indices_.pop();
		}
		return true;
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここまでコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


int main()
{
	std::string S("abcbca");
	Subsequence subseq(S);
	do
	{
		std::cout << subseq.str << std::endl;
	} while (subseq.next());

	return 0;
}