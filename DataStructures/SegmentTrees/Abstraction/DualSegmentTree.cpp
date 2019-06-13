#include <bits/stdc++.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////
// 双対セグメント木 //
//////////////////////

// Element_tを列の要素の集合として、要件は以下
// Transformation_tはElement_t上の変換全体の集合、(Monoid_t, operate_, identity_)はモノイド
// 準同型写像homoMorphism:Monoid_t->Transformation_tによりMonoid_tとTransformation_tは準同型
// これらの要件を満たすとき、Transformation_tの要素を区間に作用させた場合の最終的な合成写像を返す
template <typename Monoid_t, typename Operation_t, typename HomoMorphism_t>
class DualSegmentTree {
private:
	const Operation_t operate_;
	const Monoid_t identity_;
	const HomoMorphism_t homoMorphism_;
	std::vector<Monoid_t> container_;

	void build(const unsigned int array_size)
	{
		unsigned int length{1};
		while (length < array_size)
			length <<= 1;
		container_.resize(2 * length, identity_);
	}

	// 新しい演算ほど左にくるようにする(写像の合成と同じ順番)
	void updateHelper(const int query_l, const int query_r, const Monoid_t& added, const int node_i, const int node_l, const int node_r)
	{
		if (query_r <= node_l || node_r <= query_l) return;

		Monoid_t& monoid{container_[node_i]};
		if (query_l <= node_l && node_r <= query_r)
		{
			monoid = operate_(added, monoid);
			return;
		}

		container_[2 * node_i] = operate_(monoid, container_[2 * node_i]);
		container_[2 * node_i + 1] = operate_(monoid, container_[2 * node_i + 1]);
		monoid = identity_;
	
		const int node_m{(node_l + node_r) >> 1};
		updateHelper(query_l, query_r, added, 2 * node_i, node_l, node_m);
		updateHelper(query_l, query_r, added, 2 * node_i + 1, node_m, node_r);
	}

public:
	// initial_elementで要素配列を初期化
	DualSegmentTree(
		const unsigned int array_size,
		const Operation_t operate, const Monoid_t identity,
		const HomoMorphism_t homoMorphism
	)
		: operate_(operate), identity_(identity), homoMorphism_(homoMorphism)
	{
		build(array_size);
	}
	DualSegmentTree(const DualSegmentTree& dst)
		: container_(dst.container_), operate_(dst.operate_), identity_(dst.identity_), homoMorphism_(dst.homoMorphism_){}
	DualSegmentTree(DualSegmentTree&& dst)
		: container_(std::move(dst.container_)), operate_(dst.operate_), identity_(dst.identity_), homoMorphism_(dst.homoMorphism_){}

	// left,rightは0-indexed、半開区間[left,right)にhomoMorphism(operate)を施す
	void update(const int left, const int right, const Monoid_t added)
	{
		updateHelper(left, right, added, 1, 0, container_.size() >> 1);
	}

	// indexは0-indexed、indexの要素を返す
	auto get(const int index) const
	{
		Monoid_t monoid{identity_};
		for (int monoid_i{((int)container_.size() >> 1) + index}; monoid_i > 0; monoid_i >>= 1)
			monoid = operate_(container_[monoid_i], monoid);

		return homoMorphism_(monoid);
	}
};

template <typename Monoid_t, typename Operation_t, typename HomoMorphism_t>
decltype(auto) makeDualSegmentTree(
		const unsigned int array_size,
		const Operation_t operate, const Monoid_t identity,
		const HomoMorphism_t homoMorphism
	)
{
	return DualSegmentTree<Monoid_t, Operation_t, HomoMorphism_t>(
			array_size, operate, identity, homoMorphism
		);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここまでコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	int n, q;
	scanf("%d%d", &n, &q);
	auto dst(
		makeDualSegmentTree(
			n,
			[](const int64_t left, const int64_t right)
			{
				return left >= 0?left:right;
			},
			-1ll,
			[](const int64_t monoid)
			{
				return [=](const int64_t argument)
				{
					return monoid >= 0? monoid: argument;
				};
			}
		)
	);

	for (int q_i{}; q_i < q; q_i++)
	{
		int com;
		scanf("%d", &com);
		if (com)
		{
			int i;
			scanf("%d", &i);
			printf("%lld\n", dst.get(i)((1ll << 31) - 1));
		}
		else
		{
			int s, t, x;
			scanf("%d%d%d", &s, &t, &x);
			t++;
			dst.update(s, t, x);
		}
	}

	return 0;
}