#pragma once
#include "BST.h"

#define Balanced(x) (stature((x).lChild) == stature((x).rChild))	//理想平衡
#define BalFac(x) (stature((x).lChild) - stature((x).rChild))		//平衡因子
#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2))		//AVL平衡
#define tallerChild(x) (stature((x) -> lChild) > stature((x) -> rChild) ? (x) -> lChild : ( stature((x) -> rChild) > stature((x) -> lChild) ? (x) -> rChild : ( IsLChild(*(x)) ? (x) -> lChild : (x) -> rChild)))

template <typename T>
class AVL : public BST<T> {
public:
	BinNodePosi(T) insert(const T& e);
	bool remove(const T& e);
};

template <typename T>
BinNodePosi(T) AVL<T>::insert(const T& e) {
	BinNodePosi(T)& x = this->search(e);
	if (x) return x;
	x = new BinNode<T>(e, this->_hot);
	this->_size++;
	for (BinNodePosi(T) p = this -> _hot; p; p = p->parent) {
		if (!AvlBalanced(*p)) {
			FromParentTo(*p) = this->rotateAt(tallerChild(tallerChild(p)));
			break;
		}
		else {
			this->updateHeight(p);
		}
	}
	return x;
}

template <typename T>
bool AVL<T>::remove(const T& e) {
	BinNodePosi(T)& x = this->search(e);
	if (!x) return false;
	this->removeAt(x, this->_hot);
	this->_size--;
	for (BinNodePosi(T) p = this->_hot; p; p = p->parent) {
		if (!AvlBalanced(*p)) {
			p = FromParentTo(*p) = this->rotateAt(tallerChild(tallerChild(p)));
		}
		this->updateHeight(p);
	}
	return true;
}