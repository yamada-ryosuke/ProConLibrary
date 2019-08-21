#include "SubsequenceAutomaton.hpp"

/////////////////
// 部分列全列挙 //
/////////////////

// 使い方はnext_permutationと同様にdo-whileで回す
class Subsequence {
private:
	using Automaton_t = std::vector<std::array<int, 26>>;

	std::stack<int> indices_;
	Automaton_t automaton_;
	const char initial_char_;

	bool add(int next_c)
	{
		for (; next_c < 26; next_c++)
		{
			if (automaton_[indices_.top()][next_c] == (int)automaton_.size() - 1)
				continue;
			str.push_back('a' + next_c);
			indices_.push(automaton_[indices_.top()][next_c]);
			return true;
		}
		return false;
	}

public:
	std::string str;

	Subsequence(std::string& S, const char initial_char = 'a')
		: automaton_(subsequenceAutomaton(S, initial_char)), initial_char_(initial_char)
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