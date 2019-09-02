#include "EdgeTemplate.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////
// 強連結成分分解 //
///////////////////

// コンストラクタに隣接リストを渡すと強連結成分分解する
// Edgeは{to}
class SCC {
private:
	using vi = std::vector<int>;
	using vvi = std::vector<vi>;
	using vb = std::vector<bool>;

	const EdgeLists& edge_;
	vvi componentElements_, revEdge_;
	vi belongTo_;

	void backTrack(const int index, vi& revOrder, vb& visited)
	{
		if (visited[index]) return;
		visited[index] = true;
		for (const auto& next: edge_[index])
			backTrack(next.to, revOrder, visited);
		revOrder.push_back(index);
	}
	void assignComponent(const int index)
	{
		if (belongTo_[index] >= 0) return;
		belongTo_[index] = componentElements_.size() - 1;
		componentElements_.back().push_back(index);
		for (const auto& next: revEdge_[index])
			assignComponent(next);
	}

public:
	// belongTo[i]は元のグラフの要素iが属している強連結成分のindex
	const vi& belongTo;
	// belongToの逆像、compoenentElements.size()は強連結成分の個数
	const vvi& componentElements;

	SCC(const EdgeLists& adjacentList)
		: edge_(adjacentList), belongTo(belongTo_), componentElements(componentElements_)
	{
		revEdge_.resize(edge_.size());
		for (int i{}; i < (int)edge_.size(); i++)
			for (const auto& vertex: edge_[i])
				revEdge_[vertex.to].push_back(i);

		vb visited(edge_.size());
		vi revOrder;
		revOrder.reserve(edge_.size());
		for (int i{}; i < (int)edge_.size(); i++)
			backTrack(i, revOrder, visited);

		belongTo_.resize(edge_.size(), -1);
		for (int i{(int)revOrder.size() - 1}; i >= 0; i--)
		{
			const int index{revOrder[i]};
			if (belongTo_[index] >= 0) continue;
			componentElements_.push_back({});
			assignComponent(index);
		}
	}

	// 強連結成分を押しつぶした時のDAGを隣接リストで返す
	vvi makeDAG() const
	{
		vvi dagList(edge_.size());
		for (int from_i{}; from_i < (int)edge_.size(); from_i++)
			for (const auto& to_e: edge_[from_i])
			{
				const int dag_from{belongTo[from_i]}, dag_to{belongTo[to_e.to]};
				if (dag_from == dag_to) continue;
				dagList[dag_from].push_back(dag_to);
			}
		for (auto& e: dagList)
		{
			std::sort(e.begin(), e.end());
			e.erase(std::unique(e.begin(), e.end()), e.end());
		}
		return std::move(dagList);
	}
};