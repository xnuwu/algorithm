#pragma once
#include "PQ.h"
#include "BinTree.h"

template <typename T>
class PQLeftHeap: public PQ<T>, public BinTree<T> {
public:
	PQLeftHeap() {}
	PQLeftHeap(T* E, int n) {
		for (int i = 0; i < n; i++) {
			insert(E[i]);
		}
	}

	void insert(T e);
	T getMax();
	T delMax();
	void mergePQ(PQLeftHeap& pql) {
		merge(this->_root, pql.root());
		this->_size += pql._size;
		pql._size = 0;
	}
};

template<typename T>
static BinNodePosi(T) merge(BinNodePosi(T) a, BinNodePosi(T) b) {
	if (!a) return b;
	if (!b) return a;
	if (lt(a->data, b->data)) {
		BinNodePosi(T) t = a;
		a = b;
		b = t;
	}

	a->rChild = merge(a->rChild, b);
	a->rChild->parent = a;
	if (!a->lChild || a->lChild->npl < a->rChild -> npl) {
		BinNodePosi(T) t = a->lChild;
		a->lChild = a->rChild;
		a->rChild = t;
	}
	a->npl = a->rChild ? a->rChild->npl + 1 : 1;
	return a;
}

template <typename T>
void PQLeftHeap<T>::insert(T e) {
	BinNodePosi(T) b = new BinNode<T>(e);
	this -> _root = merge(this->_root, b);
	this->_root->parent = nullptr;
	this->_size++;
}

template<typename T>
inline T PQLeftHeap<T>::delMax()
{
	BinNodePosi(T) lc = this->_root->lChild;
	BinNodePosi(T) rc = this->_root->rChild;
	T e = this->_root->data;
	delete this->_root;
	this->_size--;
	this->_root = merge(lc, rc);
	if (this->_root) {
		this->_root->parent = nullptr;
	}

	return e;
}

template<typename T>
T PQLeftHeap<T>::getMax() {
	return this->_root->data;
}
