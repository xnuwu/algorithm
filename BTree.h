#pragma once
#include "Release.h"
#include "Queue.h"
#include "BTNode.h"

template <typename T>
class BTree {
protected:
	int _size;
	int _order;
	BTNodePosi(T) _root;
	BTNodePosi(T) _hot;

	void solveOverflow(BTNodePosi(T) n);
	void solveUnderflow(BTNodePosi(T) n);
	
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

	void printTree();
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
		p->child.insert(pr + 2, nt);
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
	if (n->child.size() >= (_order + 1) / 2) {
		std::cout << "节点 " << n << " 有" << n->child.size() << "个孩子，未下溢" << std::endl;
		return;
	}

	std::cout << "节点 " << n << " 孩子数量为 " << n->child.size() << ", 当前B树阶为" << _order << ",开始处理下溢" << std::endl;

	BTNodePosi(T) p = n->parent;

	//递归基
	if (!p) {

		std::cout << "递归到达根节点" << std::endl;
		if (!n->key.size() && n->child[0]) {

			std::cout << "根节点当前暂无元素,但是根节点孩子存在,更新根节点为孩子节点" << std::endl;
			_root = n->child[0];
			_root->parent = nullptr;
			n->child[0] = nullptr;
			Cleaner<BTNodePosi(T)>::clean(n);
		}
		return;
	}

	Rank r = p->child.search(n);

	if (r > 0) {
		BTNodePosi(T) ls = p->child[r - 1];
		//左邻借位
		if (ls->child.size() > (_order + 1) / 2) {

			std::cout << "节点 " << n << " 从父节点 " << p << " 借元素 " << p->key[r] << std::endl;
			n->key.insert(0, p->key[r]);
			
			std::cout << "节点 " << n << " 从左节点 " << ls << " 借孩子 " << ls->child[ls->child.size() - 1] << std::endl;
			n->child.insert(0, ls->child.remove(ls->child.size() - 1));

			std::cout << "父节点 " << p << " 从左子元素 " << ls << " 借元素 " << ls->key[ls->key.size() - 1] << std::endl;
			p->key[r] = ls->key[ls->key.size() - 1];

			ls->key.remove(ls->key.size() - 1);

			if (n->child[0]) {
				std::cout << n << " 修改从左邻借过来的孩子 " << n->child[0] << " 的父亲为自己" << std::endl;
				n->child[0]->parent = n;
			}
			return;
		}
	}

	if (r < p->child.size() - 1) {
		BTNodePosi(T) rs = p->child[r + 1];
		//右邻借位
		if (rs->child.size() > (_order + 1) / 2) {

			std::cout << "节点 " << n << " 从父节点 " << p <<" 借元素 "  << p->key[r] << std::endl;
			n->key.insert(p->key[r]);

			std::cout << "节点 " << n << " 从右节点 " << rs << " 借孩子 " << rs->child[0] << std::endl;
			n->child.insert(rs->child.remove(0));

			std::cout << "父节点 " << p << " 从右子元素 " << rs << " 借元素 " << rs->key[0] << std::endl;
			p->key[r] = rs->key.remove(0);
			
			if (n->child[n->child.size() - 1]) {
				std::cout << n << " 修改从右邻借过来的孩子 " << n->child[n->child.size() - 1] << " 的父亲为自己" << std::endl;
				n->child[n->child.size() - 1]->parent = n;
			}
			return;
		}
	}

	if (r > 0) {
		std::cout << n << " 准备从父亲借位元素 " << p->key[r-1] << " 将左邻居合并" << std::endl;
		BTNodePosi(T) ls = p->child[r - 1];
		
		std::cout << ls << " 添加从父亲借位的元素 " << p->key[r - 1] << std::endl;
		ls->key.insert(p->key.remove(r-1));

		std::cout << n << " 的父亲准备去除它,并准备将它合并到左邻居 " << ls << " 上" << std::endl;
		p->child.remove(r);

		while (n->key.size() > 0) {
			std::cout << "左邻 " << ls << " 添加来自 " << n << " 的元素 " << n->key[0] << std::endl;
			ls->child.insert(n->child.remove(0));
			ls->key.insert(n->key.remove(0));
			if (ls->child[ls->child.size() - 1]) {
				ls->child[ls->child.size() - 1]->parent = ls;
			}
		}
		ls->child.insert(n->child.remove(0));
		if (ls->child[ls->child.size() - 1]) {
			ls->child[ls->child.size() - 1]->parent = ls;
		}
		std::cout << "释放节点 " << n << std::endl;
		Cleaner<BTNodePosi(T)>::clean(n);
	}
	else {
		std::cout << n << " 准备从父亲借位元素 " << p->key[r] << " 合并到左邻居" << std::endl;
		BTNodePosi(T) rs = p->child[r + 1];

		std::cout << n << " 添加从父亲借位的元素 " << p->key[r] << std::endl;
		n->key.insert(p->key.remove(r));

		std::cout << rs << " 的父亲准备去除它,并准备到左节点 " << n << " 上" << std::endl;
		p->child.remove(r + 1);

		while (rs->key.size() > 0) {
			std::cout << n << " 添加来自右节点 " << rs << " 的元素 " << rs->key[0] << std::endl;
			n->child.insert(rs->child.remove(0));
			n->key.insert(rs->key.remove(0));
			if (n->child[n->child.size() - 1]) {
				n->child[n->child.size() - 1]->parent = n;
			}
		}
		n->child.insert(rs->child.remove(0));
		if (n->child[n->child.size() - 1]) {
			n->child[n->child.size() - 1]->parent = n;
		}
		std::cout << "释放节点 " << rs << std::endl;
		Cleaner<BTNodePosi(T)>::clean(rs);
	}
	
	std::cout << "准备检查父亲 " << p << " 是否存在下溢" << std::endl;
	solveUnderflow(p);
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
	printTree();
}

template<typename T>
inline bool BTree<T>::remove(const T& e)
{
	std::cout << "准备删除 " << e << std::endl;
	BTNodePosi(T) v = search(e);
	if (!v) {
		std::cout << "未找到待删除元素 " << e << std::endl;
		return false;
	}

	Rank r = v->key.search(e);
	if (v->child[r+1]) {
		BTNodePosi(T) u = v->child[r + 1];
		while (u->child[0]) {
			u = u->child[0];
		}

		std::cout << "交换节点 " << u << " 的首元素值 " << u->key[0] << " 到 " << v << " 的 " << r << " 位置,与值 " << v->key[r] << " 交换 " << std::endl;
		v->key[r] = u->key[0];
		v = u;
		r = 0;
	}
	std::cout << "删除位于 " << v << " 的元素 " << v->key[r] << std::endl;
	v->key.remove(r);
	v->child.remove(r + 1); //叶节点孩子为空,直接删除
	_size--;
	solveUnderflow(v);
	printTree();
}

template<typename T>
inline void BTree<T>::printTree()
{
	std::cout << "********************************************** 开始 **********************************************" << std::endl;

	if (!_root) {
		std::cout << "B树 " << _root << " 为空" << std::endl;
	}
	else {
		Queue<BTNodePosi(T)> queue;
		queue.enqueue(_root);
		while (!queue.empty()) {

			std::cout << std::endl;
			BTNodePosi(T) n = queue.dequeue();
			std::cout << "节点 " << n << " 的元素: ";
			for (int i = 0; i < n->key.size(); i++) {
				std::cout << n->key[i] << " ";
			}
			std::cout << std::endl;
			std::cout << "节点 " << n << " 的孩子: ";
			for (int i = 0; i < n->child.size(); i++) {
				if (n->child[i]) {
					std::cout << n->child[i] << " ";
					queue.enqueue(n->child[i]);
				}
			}
			std::cout << std::endl;
			std::cout << std::endl;
		}
	}
	std::cout << "********************************************** 结束 **********************************************" << std::endl;
	std::cout << std::endl;
}

