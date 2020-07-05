#pragma once
#include "BinTree.h"

template<typename T>
class BST : public BinTree<T> {
protected:
	BinNodePosi(T)& searchIn(BinNodePosi(T)& v, const T& e, BinNodePosi(T)& hot);
	BinNodePosi(T) removeAt(BinNodePosi(T)& x, BinNodePosi(T)& hot);

	//最后一次访问的非空节点位置
	BinNodePosi(T) _hot;

	//按照"3+4"结构，重新联机3个节点4个子树
	BinNodePosi(T) connect34(BinNodePosi(T) nodeLeft, BinNodePosi(T) nodeMid, BinNodePosi(T) nodeRight, BinNodePosi(T) llSubTree, BinNodePosi(T) lrSubTree, BinNodePosi(T) rlSubTree, BinNodePosi(T) rrSubTree);

	//对x、父亲、祖父做旋转
	BinNodePosi(T) rotateAt(BinNodePosi(T) x);

public:
	BST() : _hot(nullptr) {};
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
	}
	else if (!HasRChild(*x)) {
		succ = x = x->lChild;
	}
	else {
		w = w->succ();
		//交换data
		T tmpData = x->data;
		x->data = w->data;
		w->data = tmpData;

		BinNodePosi(T) u = w->parent;
		(u == x ? u->rChild : u->lChild) = succ = w->rChild;
	}
	hot = w->parent;
	if (succ) {
		succ->parent = hot;
	}
	release(w->data);
	release(w);
	return succ;
}

template <typename T>
BinNodePosi(T)& BST<T>::search(const T& e) {
	return searchIn(this->_root, e, _hot = nullptr);
}

template<typename T>
BinNodePosi(T) BST<T>::insert(const T& e)
{
	BinNodePosi(T)& x = search(e);
	if (x) {
		return x;
	}

	x = new BinNode<T>(e, _hot);

	++(this->_size);
	this->updateHeightAbove(x);
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
	--(this->_size);
	this->updateHeightAbove(_hot);
	return true;
}

template <typename T>
BinNodePosi(T) BST<T>::connect34(BinNodePosi(T) nodeLeft, BinNodePosi(T) nodeMid, BinNodePosi(T) nodeRight, BinNodePosi(T) llSubTree, BinNodePosi(T) lrSubTree, BinNodePosi(T) rlSubTree, BinNodePosi(T) rrSubTree) {
	nodeLeft->lChild = llSubTree;
	if (llSubTree) {
		llSubTree->parent = nodeLeft;
	}
	nodeLeft->rChild = lrSubTree;
	if (lrSubTree) {
		lrSubTree->parent = nodeLeft;
	}
	this->updateHeight(nodeLeft);

	nodeRight->lChild = rlSubTree;
	if (rlSubTree) {
		rlSubTree->parent = nodeRight;
	}
	nodeRight->rChild = rrSubTree;
	if (rrSubTree) {
		rrSubTree->parent = nodeRight;
	}
	this->updateHeight(nodeRight);

	nodeMid->lChild = nodeLeft;
	nodeLeft->parent = nodeMid;

	nodeMid->rChild = nodeRight;
	nodeRight->parent = nodeMid;

	this->updateHeight(nodeMid);

	return nodeMid;
}

template <typename T>
BinNodePosi(T) BST<T>::rotateAt(BinNodePosi(T) x) {
	BinNodePosi(T) p = x->parent;
	BinNodePosi(T) g = p->parent;

	if (IsLChild(*p)) {
		if (IsLChild(*x)) {
			p->parent = g->parent;
			return connect34(x, p, g, x->lChild, x->rChild, p->rChild, g->rChild);
		}
		else {
			x->parent = g->parent;
			return connect34(p, x, g, p->lChild, x->lChild, x->rChild, g->rChild);
		}
	}
	else {
		if (IsRChild(*x)) {
			p->parent = g->parent;
			return connect34(g, p, x, g->lChild, p->lChild, x->lChild, x->rChild);
		}
		else {
			x->parent = g->parent;
			return connect34(g, x, p, g->lChild, x->lChild, x->rChild, p->rChild);
		}
	}
}