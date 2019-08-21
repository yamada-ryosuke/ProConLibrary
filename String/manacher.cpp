#include "manacher.hpp"

// https://atcoder.jp/contests/wupc2019/tasks/wupc2019_e
int main()
{
	int M, N;
	scanf("%d%d", &M, &N);
	std::vector<int> row(2 * M - 1), column(2 * N - 1);
	for (int i{1}; i < 2 * M - 1; i += 2)
		row[i] = -1;
	for (int i{1}; i < 2 * N - 1; i += 2)
		column[i] = -1;
	for (int i{}; i < 2 * M - 1; i += 2)
		for (int j{}; j < 2 * N - 1; j += 2)
		{
			char tmp;
			scanf(" %c", &tmp);
			if (tmp == '1')
			{
				row[i]++;
				column[j]++;
			}
		}
	std::vector<int> rowRot(manacher(row)), columnRot(manacher(column));
	int64_t row_count{}, column_count{};
	for (int border{1}; border < (int)rowRot.size(); border += 2)
	{
		int top{(border + -1) / 2}, bottom{(border + (int)rowRot.size()) / 2};
		if (top - rowRot[top] == -1 && bottom + rowRot[bottom] == (int)rowRot.size())
			row_count++;
	}
	for (int border{1}; border < (int)columnRot.size(); border += 2)
	{
		int left{(border + -1) / 2}, right{(border + (int)columnRot.size()) / 2};
		if (left - columnRot[left] == -1 && right + columnRot[right] == (int)columnRot.size())
			column_count++;
	}
	printf("%lld\n", row_count * column_count);

	return 0;
}