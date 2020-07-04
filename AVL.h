#pragma once
#include "BST.h"

#define Balanced(x) (stature((x).lChild) == stature((x).rChild))	//理想平衡
#define BalFac(x) (stature((x).lChild) - stature((x).rChild))		//平衡因子
#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2))		//AVL平衡

template<typename T>
class AVL : public BST<T> {
public:
	BinNodePosi(T) insert(const T& e);
	bool remove(const T& e);
};