#include <bits/stdc++.h>

/////////////////
// SuffixArray //
/////////////////

class SuffixArray {
private:
	std::vector<int> result_;

	// 文字列のコード(>0)を受け取る.
	// 番兵0は呼び出し元で入れておく.
	std::vector<int> sais(const std::vector<int>& array, const int char_num) const
	{
		const int size{(int)array.size()};

		// S型L型の判定
		std::vector<bool> isSmall(size);
		isSmall.back() = true;
		for (int i{size - 2}; i >= 0; i--)
		{
			if (array[i] != array[i + 1])
				isSmall[i] = array[i] < array[i + 1];
			else
				isSmall[i] = isSmall[i + 1];
		}

		// バケットの作成
		// iのためのバケットは[bucket[i - 1], bucket[i])で表される.
		std::vector<int> bucket(char_num + 1);
		for (const auto& num: array)
			bucket[num]++;
		for (int i{}; i < char_num; i++)
			bucket[i + 1] += bucket[i];

		// LMS-substringのソートの為のinduced sort
		// lmsIndicesにはLMSの位置が昇順に入る
		std::vector<int> lmsIndices;
		lmsIndices.reserve(size >> 1);
		for (int i{1}; i < size; i++)
			if (isSmall[i] && !isSmall[i - 1])
				lmsIndices.push_back(i);
		std::vector<int> suffixArray(inducedSort(array, char_num, isSmall, bucket, lmsIndices));

		// lmsIndicesの逆写像
		std::vector<int> lmsIndicesInv(size, -1);
		for (int i{}; i < (int)lmsIndices.size(); i++)
			lmsIndicesInv[lmsIndices[i]] = i;

		// LMS-substringのコード化
		// codeArray:LMS-substringのコードがarrayに出てくる順番に入る.
		std::vector<int> codeArray(lmsIndices.size());
		int code_num{};
		for (int i{1}, prev_begin{size - 1}, prev_end{size}; i < size; i++)
		{
			const int& begin{suffixArray[i]};
			if (begin == 0) continue;
			if (!isSmall[begin] || isSmall[begin - 1]) continue;

			int end{lmsIndices[lmsIndicesInv[begin] + 1] + 1};
			if (!areEqual(array.begin() + begin, array.begin() + end, array.begin() + prev_begin, array.begin() + prev_end))
				code_num++;
			codeArray[lmsIndicesInv[begin]] = code_num;
			prev_begin = begin;
			prev_end = end;
		}
		
		// LMS-substringのsuffix array
		std::vector<int> lmsSA;
		if (code_num + 1 == (int)codeArray.size())
		{
			lmsSA.resize(codeArray.size());
			for (int i{}; i < (int)codeArray.size(); i++)
				lmsSA[codeArray[i]] = i;
		}
		else
			lmsSA = sais(codeArray, code_num);

		// 正しいinduced sort
		std::vector<int> sortedLmsIndices(lmsIndices.size());
		for (int i{}; i < (int)lmsIndices.size(); i++)
			sortedLmsIndices[(int)lmsIndices.size() - 1 - i] = lmsIndices[lmsSA[i]];
		return inducedSort(array, char_num, isSmall, bucket, sortedLmsIndices);
	}

	template <typename Iterator>
	bool areEqual(const Iterator begin1, const Iterator end1, const Iterator begin2, const Iterator end2) const
	{
		if (end1 - begin1 != end2 - begin2) return false;
		for (int i{}; begin1 + i != end1; i++)
			if (begin1[i] != begin2[i])
				return false;
		return true;
	}

	std::vector<int> inducedSort(const std::vector<int>& array, const int char_num, const std::vector<bool>& isSmall, const std::vector<int>& bucket, const std::vector<int>& lmsIndices) const
	{
		// lmsの追加
		const int size{(int)array.size()};
		std::vector<int> suffixArray(size, -1);
		std::vector<int> moveCounter(char_num + 1);
		for (auto& lms_i: lmsIndices)
		{
			moveCounter[array[lms_i]]++;
			suffixArray[bucket[array[lms_i]] - moveCounter[array[lms_i]]] = lms_i;
		}
		std::fill(moveCounter.begin(), moveCounter.end(), 0);

		// L型の追加
		for (auto& num: suffixArray)
		{
			if (num <= 0) continue;
			const int& next{array[num - 1]};
			if (isSmall[num - 1]) continue;
			suffixArray[bucket[next - 1] + moveCounter[next]] = num - 1;
			moveCounter[next]++;
		}
		std::fill(moveCounter.begin(), moveCounter.end(), 0);

		// S型の追加
		for (int i{size - 1}; i > 0; i--)
		{
			const int& now{suffixArray[i]};
			if (now == 0) continue;
			const int& next{array[now - 1]};
			if (!isSmall[now - 1]) continue;
			moveCounter[next]++;
			suffixArray[bucket[next] - moveCounter[next]] = now - 1;
		}

		return suffixArray;
	}

public:
	const std::vector<int>& result;

	SuffixArray(const std::string& str, const char initial_char = 'a')
		: result(result_)
	{
		// 文字列のコード化
		std::vector<int> numberArray(str.size() + 1);
		for (int i{}; i < (int)str.size(); i++)
			numberArray[i] = str[i] - initial_char + 1;

		result_ = sais(numberArray, 26);
	}
};