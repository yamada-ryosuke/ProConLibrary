#include "calcTreeDiameter.hpp"

int main()
{
	int n;
	scanf("%d", &n);
	EdgeLists graph(n);
	for (int i{}; i < n - 1; i++)
	{
		int s, t, w;
		scanf("%d%d%d", &s, &t, &w);
		graph[s].push_back({t, w});
		graph[t].push_back({s, w});
	}
	printf("%lld\n", std::get<2>(calcTreeDiameter(graph)));

	return 0;
}