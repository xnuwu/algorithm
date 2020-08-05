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
	BTree(int order = 3): _order(order), _size(0) {
		_root = new BTNode<T>();
		std::cout << "init btree _root " << _root << std::endl;
	}

	~BTree() {
		if (_root) {
			std::cout << "release btree " << _root << std::endl;
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

	std::cout << "start solveOverflow" << std::endl;

	//待提升的节点下标
	Rank mid = _order / 2;
	
	BTNodePosi(T) nt = new BTNode<T>();
	//最后一个元素下标为_order - 1
	for (int i = 0; i < _order - 1 - mid; i++) {
		nt->key.insert(i, n->key.remove(mid + 1));
		nt->child.insert(i, n->child.remove(mid + 1));
		std::cout << "new BtNode insert " << i << " at " << nt << i << std::endl;
	}
	//最右边孩子
	nt->child.insert(_order - 1 - mid, n->child.remove(mid + 1));

	for (int i = 0; i < nt->child.size(); i++) {
		std::cout << "try set nt -> child[" << i << "] parent " << nt->child[i] << std::endl;
		if (nt->child[i]) {
			std::cout << "set " << nt ->child[i] << " parent " << nt << std::endl;
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
		solveOverflow(p);
	}
	else {
		//重新分配根节点
		_root = new BTNode<T>(e, n, nt);
	}
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
	_hot->child.insert(r + 1, nullptr);
	_size++;
	std::cout << "insert " << e << " at " << _hot << " index " << r + 1 << std::endl;
	solveOverflow(_hot);
}

