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
	void solveOverflow(BTNodePosi(T));
	
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