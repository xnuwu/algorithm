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
	void insert(const T& e);
	bool remove(const T& e);
};

template<typename T>
inline void BTree<T>::solveOverflow(BTNodePosi(T) n)
{
	if (n && n->child.size() <= _order) return;

	//分裂
	Rank mid = _order / 2;
	BTNodePosi(T) nt = new BTNode<T>();
	for (int i = 0; i < _order - mid - 1; i++) {
		nt->key.insert(i, n->key.remove(mid + 1));
		nt->child->insert(i, n->child.remove(mid + 1));
	}
	nt->child.insert(_order - mid - 1, n->child.remove(mid + 1));
	if (nt->child[0]) {
		for (int i = 0; i < nt->child.size(); i++) {
			nt->child[i]->parent = nt;
		}
	}
	T e = n->key.remove(mid);

	//合并父级
	BTNodePosi(T) p = n->parent;
	if (p) {
		Rank pr = p->key.search(e);
		p->key.insert(pr + 1, e);
		p->child.insert(pr + 1, nt);
		nt->parent = p;
	}
	else {
		//根节点
		_root = new BTNode<T>(e, n, nt);
	}
	solveOverflow(p);
}

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

template<typename T>
void BTree<T>::insert(const T& e)
{
	if (search(e)) { return; }
	Rank r = _hot->key.search(e);
	_hot->key.insert(r + 1, e);
	_hot->child->insert(r + 1, nullptr);
	_size++;
	solveOverflow(_hot);
}

