#pragma once
#include <algorithm>
#include "BST.h"
#define IsBlack(p) (!(p) || (RB_BLACK == (p)->color))
#define IsRed(p) (!IsBlack(p))
#define BlackHeightUpdated(x) (	\
	((stature((x).lChild) == (stature((x).rChild))  && \
	((stature(x) == ((IsRed(x) ? stature((x).lChild) : (stature((x).lChild) + 1)))) \
)

template<typename T> class RedBalckTree : public BST<T>{
protected:
	void solveDoubleBlack(BinNodePosi(T) p);
	void solveDoubleRed(BinNodePosi(T) x);
	int updateHeight(BinNodePosi(T) p);
public:
	BinNodePosi(T) insert(T& e);
	bool remove(const T& e);
};

template<typename T>
inline void RedBalckTree<T>::solveDoubleBlack(BinNodePosi(T) p)
{
	std::cout << "开始解决节点 " << p << " 双黑冲突" << std::endl;
}

template<typename T>
inline void RedBalckTree<T>::solveDoubleRed(BinNodePosi(T) x)
{
	//如果是根节点直接置黑
	if (IsRoot(x)) {
		x->color = RB_BLACK;
		x->height++;
		return;
	}
	BinNodePosi(T) p = x->parent;
	BinNodePosi(T) g = p->parent;
	BinNodePosi(T) u = uncle(x);

	if (p->color == RB_BLACK) {
		return;
	}

	//处理双红节点
	if (IsBlack(u)) {
		//zig-zag、zig-zig变换后3+4调整树结构，重写染色
		if (IsLChild(x) == IsLChild(p)) {
			p->color = RB_BLACK;
		}
		else if (IsRChild(x) == IsRChild(p)) {
			p->color = RB_BLACK;
		}
		else {
			x->color = RB_BLACK;
		}
		g->color = RB_RED;
		BinNodePosi(T) r = FromParentTo(*g) = rotateAt(x);
		r->parent = g->parent;
	}
	else {
		p->color = RB_BLACK; p->height++;
		u->color = RB_BLACK; u->height++;
		if (!IsRoot(*g)) {
			g->color = RB_BLACK;
		}
		solveDoubleRed(g);
	}
}

template<typename T>
inline int RedBalckTree<T>::updateHeight(BinNodePosi(T) p)
{
	p->height = std::max(stature((p)->lChild), stature((p)->rChild));
	return IsBlack(p) ? p->height++ : p->height;
}

template<typename T>
inline BinNodePosi(T) RedBalckTree<T>::insert(T& e)
{
	BinNodePosi(T)& x = search(e);
	if (x) {
		return x;
	}
	x = new BinNode<T>(e, _hot, nullptr, nullptr, -1);
	_size++;
	solveDoubleRed(x);
	return x;
}

template<typename T>
inline bool RedBalckTree<T>::remove(const T& e)
{
	BinNodePosi(T)& x = search(e);
	if (!x) {
		std::cout << "未找到待删除的元素 " << e << std::endl;
		return false;
	}

	BinNodePosi(T) r = removeAt(x, _hot);
	if (--_size <= 0) {
		std::cout << "已删除最后一个节点，当前红黑树为空" << std::endl;
		return true;
	}

	if (!_hot) {
		std::cout << "当前删除的是根节点,自动设置接替的元素颜色为【黑】" << std::endl;
		_root->color = RB_BLACK;
		updateHeight(_root);
		return true;
	}

	if (BlackHeightUpdated(*r)) {
		std::cout << "删除元素后,当前节点黑高度平稳,无需重构拓扑、重染色" << std::endl;
		return true;
	}

	if (IsRed(r)) {
		std::cout << "删除 " << e << " 后，接替的元素颜色为红，直接置【黑】,更新高度" << std::endl;
		r->color = RB_BLACK;
		r->height++;
		return true;
	}

	solveDoubleBlack(r);
	return true;
}
