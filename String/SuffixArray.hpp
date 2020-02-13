#include <bits/stdc++.h>

/////////////////
// SuffixArray //
/////////////////

class SuffixArray {
private:
	std::vector<int> result_;

	// 文字列のコード(>0)を受け取る.
	// 番兵0は呼び出し元で入れておく.
	std::vector<int> sais(const std::vector<int>& array, const int char_num)
	{
		const int size{(int)array.size()};
		if (size == 1) return {0};

		// S型L型の判定
		std::vector<bool> isSmall(size);
		isSmall.back() = true;
		for (int i{size - 2}; i >= 0; i--)
		{
			if (array[i] < array[i + 1])
				isSmall[i] = true;
			else if (array[i] > array[i + 1])
				isSmall[i] = false;
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
		std::vector<int> lmsIndices;
		lmsIndices.reserve(size >> 1);
		for (int i{1}; i < size; i++)
			if (isSmall[i] && !isSmall[i - 1])
				lmsIndices.push_back(i);
		std::vector<int> suffixArray(inducedSort(array, char_num, isSmall, bucket, lmsIndices));

		// LMS-substringのコード化
		std::vector<int> codeMap(size, -1);
		int code_num{};
		codeMap.back() = 0;
		for (int i{1}, prev_begin{size - 1}, prev_end{size}; i < size; i++)
		{
			const int& begin{suffixArray[i]};
			if (begin == 0) continue;
			if (!isSmall[begin] || isSmall[begin - 1]) continue;

			int end{begin + 1};
			while (!isSmall[end] || isSmall[end - 1])
				end++;
			end++;
			if ([&]()
				{
					for (int i{}; begin + i < end && prev_begin + i < prev_end; i++)
						if (array[begin + i] != array[prev_begin + i])
							return false;
					return end - begin == prev_end - prev_begin;
				}()
			)
				continue;
			
			code_num++;
			codeMap[begin] = code_num;
			prev_begin = begin;
			prev_end = end;
		}
		
		std::vector<int> codeArray, codeArrayMap;
		codeArray.reserve(lmsIndices.size());
		codeArrayMap.reserve(lmsIndices.size());
		for (int i{}; i < size; i++)
		{
			if (codeMap[i] < 0) continue;
			codeArray.push_back(codeMap[i]);
			codeArrayMap.push_back(i);
		}
		
		// LMS-substringのsuffix array
		std::vector<int> lmsSA{sais(codeArray, code_num)};

		// 正しいinduced sort
		for (int i{}; i < (int)lmsIndices.size(); i++)
			lmsIndices[(int)lmsIndices.size() - 1 - i] = codeArrayMap[lmsSA[i]];
		return inducedSort(array, char_num, isSmall, bucket, lmsIndices);
	}

	std::vector<int> inducedSort(const std::vector<int>& array, const int char_num, const std::vector<bool>& isSmall, const std::vector<int>& bucket, const std::vector<int>& lmsIndices)
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