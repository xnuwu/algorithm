#pragma once
#include "BST.h"

#define Balanced(x) (stature((x).lChild) == stature((x).rChild))	//����ƽ��
#define BalFac(x) (stature((x).lChild) - stature((x).rChild))		//ƽ������
#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2))		//AVLƽ��

template<typename T>
class AVL : public BST<T> {
public:
	BinNodePosi(T) insert(const T& e);
	bool remove(const T& e);
};