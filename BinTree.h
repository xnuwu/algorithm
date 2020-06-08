#pragma once
#include "BinNode.h"

template <typename T>
class BinTree {
protected:
	int _size;
	BinNodePosi(T) _root;
	virtual int updateHeight(BinNodePosi(T) x);
	void updateHeightAbove(BinNodePosi(T) x);

public:
	BinTree() : _size(0), _root(nullptr) {}
	~BinTree() { if (0 < _size) { remove(_root); } }
	int size() const { return _size; }
	bool empty() const { return !_root; }
	BinNodePosi(T) root() const { return _root; }
	BinNodePosi(T) insertAsRoot(T const& e);
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e);
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e);
	BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>*& T);
	BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>*& T);
	int remove(BinNodePosi(T) x);
	BinTree<T>* secede(BinNodePosi(T) x);

	//子树层级遍历
	template <typename VST> void travLevel(VST& visit) {
		if (_root) {
			_root->travLevel(visit);
		}
	}

	//子树先序遍历
	template <typename VST> void travPre(VST& visit) {
		if (_root) {
			_root->travPre(visit);
		}
	}

	//子树中序遍历
	template <typename VST> void travIn(VST& visit) {
		if (_root) {
			_root->travIn(visit);
		}
	}

	//子树后序遍历
	template <typename VST> void travPost(VST& visit) {
		if (_root) {
			_root->travPost(visit);
		}
	}

	//比较器、判等器
	bool operator<(BinTree<T> const& bt) {
		return _root && bt._root && _root < bt._root;
	}

	bool operator=(BinTree<T> const& bt) {
		return _root && bt._root && _root == bt._root;
	}
};

template<typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x)
{
	return x->height = 1 + std::max(stature(x->lChild), stature(x->rChild));
}

template<typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x)
{
	while (x) {
		uploadHeight(x);
		x = x->parent;
	}
}

template<typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(T const& e)
{
	_size = 1;
	return _root = new BinNode<T>(e);
}

template<typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const& e)
{
	_size++;
	x->insertAsLC(e);
	updateHeightAbove(x);
	return x->lChild;
}

template<typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const& e)
{
	_size++;
	x->insertAsRC(e);
	updateHeightAbove(x);
	return x->rChild;
}
