#pragma once
#include <algorithm>
#include "BinNode.h"
#include "Release.h"

template <typename T>
class BinTree
{
	//比较器、判等器
	friend bool operator<(BinTree<T> const& lbt, BinTree<T> const& rbt)
	{
		return lbt._root && rbt._root && lbt._root < rbt._root;
	};

	friend bool operator>(BinTree<T> const& lbt, BinTree<T> const& rbt)
	{
		return lbt._root && rbt._root && lbt._root > rbt._root;
	};

	friend bool operator==(BinTree<T> const& lbt, BinTree<T> const& rbt)
	{
		return lbt._root && rbt._root && lbt._root == rbt._root;
	};
protected:
	int _size;
	BinNodePosi(T) _root;
	virtual int updateHeight(BinNodePosi(T) x);
	void updateHeightAbove(BinNodePosi(T) x);

public:
	BinTree() : _size(0), _root(nullptr) {}
	~BinTree()
	{
		if (0 < _size)
		{
			remove(_root);
		}
	}

	BinTree& operator=(const BinTree<T> bt) const {
		if (this != &bt) {
			this->_size = bt._size;
			this->_root = bt._root;
		}

		return *this;
	}

	int size() const { return _size; }
	bool empty() const { return !_root; }
	BinNodePosi(T) root() const { return _root; }
	BinNodePosi(T) insertAsRoot(T const &e);
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const &e);
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const &e);
	BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T> *&T);
	BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T> *&T);
	int remove(BinNodePosi(T) x);
	BinTree<T> *secede(BinNodePosi(T) x);

	//子树层级遍历
	template <typename VST>
	void travLevel(VST &visit)
	{
		if (_root)
		{
			_root->travLevel(visit);
		}
	}

	//子树先序遍历
	template <typename VST>
	void travPre(VST &visit)
	{
		if (_root)
		{
			_root->travPre(visit);
		}
	}

	//子树中序遍历
	template <typename VST>
	void travIn(VST &visit)
	{
		if (_root)
		{
			_root->travIn(visit);
		}
	}

	//子树后序遍历
	template <typename VST>
	void travPost(VST &visit)
	{
		if (_root)
		{
			_root->travPost(visit);
		}
	}

private:
	int removeAt(BinNodePosi(T) x);
};

template <typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x)
{
	return x->height = 1 + (stature(x->lChild) > stature(x->rChild) ? stature(x->lChild) : stature(x->rChild));
}

template <typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x)
{
	while (x)
	{
		updateHeight(x);
		x = x->parent;
	}
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(T const &e)
{
	_size = 1;
	return _root = new BinNode<T>(e);
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const &e)
{
	_size++;
	x->insertAsLC(e);
	updateHeightAbove(x);
	return x->lChild;
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const &e)
{
	_size++;
	x->insertAsRC(e);
	updateHeightAbove(x);
	return x->rChild;
}

template <typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T> *&st)
{
	if (x->lChild = st->_root)
	{ //空树检查
		x->lChild->parent = x;
	}
	_size += st->_size;
	updateHeightAbove(x);

	st->size = 0;
	st->_root = nullptr;
	release(st);
	st = nullptr;
	return x;
}

template <typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T> *&st)
{
	if (x->rChild = st->_root)
	{
		x->rChild->parent = x;
	}

	_size += st->_size;
	updateHeightAbove(x);

	st->_size = 0;
	st->_root = nullptr;
	release(st);
	st = nullptr;
	return x;
}

template <typename T>
int BinTree<T>::remove(BinNodePosi(T) x)
{
	FromParentTo(*x) = nullptr;
	updateHeightAbove(x->parent);
	int n = removeAt(x);
	_size -= n;
	return n;
}

template <typename T>
BinTree<T> *BinTree<T>::secede(BinNodePosi(T) x)
{
	FromParentTo(*x) = nullptr;
	_size -= x->size();
	updateHeightAbove(x->parent);

	BinTree<T> *st = new BinTree<T>();
	st->_root = x;
	st->_size = x->size();
	x->parent = nullptr;
	return st;
}

template <typename T>
int BinTree<T>::removeAt(BinNodePosi(T) x)
{
	if (!x)
		return 0;
	int n = 1 + removeAt(x->lChild) + removeAt(x->rChild);
	release(x->data);
	release(x);
	x = nullptr;
	return n;
}
