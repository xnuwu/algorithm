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

	void solveOverflow(BTNodePosi(T) n);
	void solveUnderflow(BTNodePosi(T));
	
public:
	BTree(int order = 3): _order(order), _size(0) {
		_root = new BTNode<T>();
		std::cout << "初始化二叉树，根节点 " << _root << std::endl;
	}

	~BTree() {
		if (_root) {
			std::cout << "释放销毁二叉树 " << _root << std::endl;
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
	if (n && n->child.size() <= _order) {
		std::cout << n << " 节点孩子未满,共" << n->child.size() << "个,B树阶为" << _order << std::endl;
		return;
	}
	std::cout << n << " 节点已满,开始分裂 " << std::endl;

	//待提升的节点下标
	Rank mid = _order / 2;
	
	BTNodePosi(T) nt = new BTNode<T>();
	std::cout << "创建新节点 " << nt << std::endl;
	//最后一个元素下标为_order - 1
	for (int i = 0; i < _order - 1 - mid; i++) {
		nt->key.insert(i, n->key.remove(mid + 1));
		nt->child.insert(i, n->child.remove(mid + 1));
		std::cout << "新节点 " << nt << " 位置 " << i << " 插入 "<< nt->key[i] << std::endl;
	}
	//最右边孩子
	nt->child[_order - 1 - mid] = n->child.remove(mid + 1);

	std::cout << "新节点当前有" << nt->child.size() << "个孩子," << nt->key.size() << "个元素"<< std::endl;
	for (int i = 0; i < nt->child.size(); i++) {
		if (nt->child[i]) {
			std::cout << "设置 " << nt ->child[i] << " 的父亲为 " << nt << std::endl;
			nt->child[i]->parent = nt;
		}
	}
	T e = n->key.remove(mid);
	//合并父级
	BTNodePosi(T) p = n->parent;
	if (p) {
		std::cout << "将元素" << e << "插入 " << n << " 的父节点" << p << std::endl;
		Rank pr = p->key.search(e);
		p->key.insert(pr + 1, e);
		p->child.insert(pr + 1, nt);
		nt->parent = p;
		solveOverflow(p);
	}
	else {
		//重新分配根节点
		_root = new BTNode<T>(e, n, nt);
		std::cout << "当前为根节点分裂，重新生成根节点 " << _root << " 根节点值 " << e << " 左孩子 " << n << " 右孩子 " << nt << std::endl;
	}
}

template<typename T>
inline void BTree<T>::solveUnderflow(BTNodePosi(T) n)
{

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
	std::cout << _hot << " 插入 " << e << std::endl;
	solveOverflow(_hot);
}

template<typename T>
inline bool BTree<T>::remove(const T& e)
{
	BTNodePosi(T) v = search(e);
	if (!v) {
		return false;
	}
}

