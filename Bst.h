#pragma once
#include "BinTree.h"

template<typename T>
class BST : public BinTree<T> {
private:
	BinNodePosi(T)& searchIn(BinNodePosi(T)& v, const T& e, BinNodePosi(T)& hot);
protected:

	//���һ�η��ʵķǿսڵ�λ��
	BinNodePosi(T) _hot;

	//����"3+4"�ṹ����������3���ڵ�4������
	BinNodePosi(T) connect34(BinNodePosi(T) nodeLeft, BinNodePosi(T) nodeMid, BinNodePosi(T) nodeRight, BinNodePosi(T) llSubTree, BinNodePosi(T) lrSubTree, BinNodePosi(T) rlSubTree, BinNodePosi(T) rrSubTree);

	//��x�����ס��游����ת
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

template <typename T>
BinNodePosi(T)& BST<T>::search(const T& e) {
	return searchIn(_root, e, nullptr);
}

template<typename T>
BinNodePosi(T) BST<T>::insert(const T& e)
{
	BinNodePosi(T) x = search(e);
	if (x) {
		return x;
	}

	x = new BinNode<T>(e, _hot);

	++_size;
	updateHeightAbove(x);
	return x;
}
