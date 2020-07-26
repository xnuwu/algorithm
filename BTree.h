#pragma once
#include "Release.h"
#include "BTNode.h"

template <typename T>
class BTree {
protected:
	int _size;
	int _order;
	BTNodePosi(T) _root;
	BTNodePosi(T) _hot;

	void solveOverflow(BTNodePosi(T));
	void solveUnderflow(BTNodePosi(T));
	
public:
	BTree(int order = 3): _order(order), size(0) {
		_root = new BTNode<T>();
	}

	~BTree() {
		if (_root) {
			Cleaner<BTNodePosi(T)>::clean(_root);
		}
	}

	int const order() {
		return _order;
	}

	int const size() {
		return _size;
	}

	BTNodePosi(T)& root() {
		return _root;
	}

	bool empty() const {
		return !_root;
	}

	BTNodePosi(T) search(const T& e);
	bool insert(const T& e);
	bool remove(const T& e);
};

template<typename T>
BTNodePosi(T) BTree<T>::search(const T& e)
{
	BTNodePosi(T) p = _root;
	_hot = nullptr;
	while (p) {
		Rank r = p->key.search(e);
		if (r >= 0 && p->key[r] == e) {
			return p;
		}
		_hot = p;
		p = p->child[r + 1];
	}

	return nullptr;
}

