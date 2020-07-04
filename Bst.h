#pragma once
#include "BinTree.h"

template<typename T>
class BST : public BinTree<T> {
private:
	BinNodePosi(T)& searchIn(BinNodePosi(T)& v, const T& e, BinNodePosi(T)& hot);
	BinNodePosi(T) removeAt(BinNodePosi(T)& x, BinNodePosi(T)& hot);
protected:

	//最后一次访问的非空节点位置
	BinNodePosi(T) _hot;

	//按照"3+4"结构，重新联机3个节点4个子树
	BinNodePosi(T) connect34(BinNodePosi(T) nodeLeft, BinNodePosi(T) nodeMid, BinNodePosi(T) nodeRight, BinNodePosi(T) llSubTree, BinNodePosi(T) lrSubTree, BinNodePosi(T) rlSubTree, BinNodePosi(T) rrSubTree);

	//对x、父亲、祖父做旋转
	BinNodePosi(T) rotateAt(BinNodePosi(T) x);

public:
	virtual BinNodePosi(T)& search(const T& e);
	virtual BinNodePosi(T) insert(const T& e);
	virtual bool remove(const T& e);
};

template<typename T>
BinNodePosi(T)& BST<T>::searchIn(BinNodePosi(T)& v, const T& e, BinNodePosi(T)& hot)
{
	if (!v || v->data == e) return v;
	_hot = v;
	return searchIn((v->data < e ? v->rChild : v->lChild), e, _hot);
}

template<typename T>
BinNodePosi(T) BST<T>::removeAt(BinNodePosi(T)& x, BinNodePosi(T)& hot)
{
	BinNodePosi(T) w = x;
	BinNodePosi(T) succ = nullptr;

	if (!HasLChild(*x)) {
		succ = x = x->rChild;
	}else if (!HasRChild(*x)) {
		succ = x = x->lChild;
	}
	else {
		succ = x->succ();
		//交换data
		T tmpData = x->data;
		x->data = succ->data;
		succ->data = tmpData;

		BinNodePosi(T) u = succ->parent;
		(u == x ? u -> rChild : u-> lChild) = succ = x->rChild;
	}
	hot = w->parent;
	if (succ) {
		succ->parent = hot;
	}
	Cleaner<T>::release(w->data);
	Cleaner<BinNodePosi(T)>::release(w);
	return succ;
}

template <typename T>
BinNodePosi(T)& BST<T>::search(const T& e) {
	return searchIn(_root, e, nullptr);
}

template<typename T>
BinNodePosi(T) BST<T>::insert(const T& e)
{
	BinNodePosi(T)& x = search(e);
	if (x) {
		return x;
	}

	x = new BinNode<T>(e, _hot);

	++_size;
	updateHeightAbove(x);
	return x;
}

template<typename T>
inline bool BST<T>::remove(const T& e)
{
	BinNodePosi(T) x = search(e);
	if (!x) {
		return false;
	}

	removeAt(x, _hot);
	--_size;
	updateHeightAbove(_hot);
	return true;
}
