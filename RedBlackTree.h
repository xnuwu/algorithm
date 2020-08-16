#pragma once
#include <algorithm>
#include "BST.h"
#define IsBlack(p) (!(p) || (RB_BLACK == (p)->color))
#define IsRed(p) (!IsBlack(p))
#define BlackHeightUpdated(x) ((stature((x).lChild) == stature((x).rChild)) && ((x).height == (IsRed(&x) ? stature((x).lChild) : stature((x).lChild) + 1)) )

template<typename T> class RedBalckTree : public BST<T>{
protected:
	void solveDoubleBlack(BinNodePosi(T) r);
	void solveDoubleRed(BinNodePosi(T) x);
	int updateHeight(BinNodePosi(T) p);
public:
	BinNodePosi(T) insert(const T& e);
	bool remove(const T& e);
	void printTree();
};

template<typename T>
inline void RedBalckTree<T>::solveDoubleBlack(BinNodePosi(T) r)
{
	std::cout << "开始解决节点 " << r << " 双黑冲突" << std::endl;
	BinNodePosi(T) p = r ? r->parent : this ->_hot;
	if (!p) {
		std::cout << "到达根节点,结束!" << std::endl;
		return;
	}
	BinNodePosi(T) s = r == p->lChild ? p->rChild : p->lChild;

	if (IsBlack(s)) {
		BinNodePosi(T) t = nullptr;
		if (HasLChild(*s) && s->lChild->color == RB_RED) t = s->lChild;
		if (HasRChild(*s) && s->rChild->color == RB_BLACK) t = s->rChild;
		if (t) {
			std::cout << r << " 的兄弟节点 " << s << " 的孩子有红节点 " << t << " 准备进行3+4重构，然后重染色! " << std::endl;
			RBColor oldColor = p->color;
			std::cout << "先记住父节点 " << p << " 的颜色为 " << oldColor << std::endl;
			BinNodePosi(T) newP = FromParentTo(*p) = this->rotateAt(t);
			if (HasLChild(*newP)) {
				newP->lChild->color = RB_BLACK;
				updateHeight(newP->lChild);
			}
			else if(HasRChild(*newP)) {
				newP->rChild->color = RB_BLACK;
				updateHeight(newP->rChild);
			}
			newP->color = oldColor;
			updateHeight(newP);
		}
		else {
			std::cout << r << " 的兄弟节点 " << s << " 的孩子都是黑色"<< std::endl;
			s->color = RB_RED;
			s->height--;
			if (IsRed(p)) {
				p->color = RB_BLACK;
			}
			else {
				p->height--;
				solveDoubleBlack(p);
			}
		}
	}
	else {
		std::cout << r << " 的兄弟节点 " << s << " 为红色,准备进行重染色、旋转，然后解决双黑冲突" << std::endl;
		s->color = RB_BLACK;
		p->color = RB_RED;

		BinNodePosi(T) t = IsLChild(*s) ? s->lChild : s->rChild;
		this->_hot = p;
		FromParentTo(*p) = this ->rotateAt(t);
		solveDoubleBlack(r);
	}
}

template<typename T>
inline void RedBalckTree<T>::solveDoubleRed(BinNodePosi(T) x)
{
	std::cout << "准备检测 " << x << " 是否存在双红冲突" << std::endl;
	if (IsRoot(*x)) {
		std::cout << x << " 为根节点,直接置黑,结束检测" << std::endl;
		x->color = RB_BLACK;
		x->height++;
		return;
	}
	BinNodePosi(T) p = x->parent;
	if (IsBlack(p)) {
		std::cout << "节点 " << x << " 的父节点 " << p << " 为黑色节点,不存在双红冲突,结束检测" << std::endl;
		return;
	}
	std::cout << "节点 " << x << " 的父节点 " << p << " 为红色节点" << std::endl;

	BinNodePosi(T) g = p->parent;
	BinNodePosi(T) u = uncle(x);

	std::cout << x << " 的祖父节点 " << g << " 元素值 " << g->data << " 颜色 " << (g->color == RBColor::RB_BLACK ? "黑色" : "红色") << std::endl;
	if (u) {
		std::cout << x << " 的叔叔节点 " << u << " 元素值 " << u->data << " 颜色 " << (u->color == RBColor::RB_BLACK ? "黑色" : "红色") << std::endl;
	}
	else {
		std::cout << x << " 的叔叔节点为空,默认黑色" << std::endl;
	}

	if (IsBlack(u)) {
		
		if (IsLChild(*x) == IsLChild(*p)) {
			p->color = RB_BLACK;
		}
		else {
			x->color = RB_BLACK;
		}
		g->color = RB_RED;
		BinNodePosi(T) r = FromParentTo(*g) = this ->rotateAt(x);
		std::cout << "重染色,然后3+4调整 " << x << " 节点" << std::endl;
	}
	else {
		p->color = RB_BLACK; p->height++;
		u->color = RB_BLACK; u->height++;
		if (!IsRoot(*g)) {
			g->color = RB_RED;
		}
		std::cout << "重染色后,准备检测祖父节点 " << g << " 是否存在双红" << std::endl;
		printTree();
		solveDoubleRed(g);
	}
}

template<typename T>
inline int RedBalckTree<T>::updateHeight(BinNodePosi(T) p)
{
	p->height = std::max(stature((p)->lChild), stature((p)->rChild));
	return IsBlack(p) ? p->height++ : p->height;
}

template<typename T>
inline BinNodePosi(T) RedBalckTree<T>::insert(const T& e)
{
	std::cout << std::endl;
	std::cout << "准备插入元素 " << e << std::endl;
	BinNodePosi(T)& x = this -> search(e);
	if (x) {
		std::cout << "待插入的元素 " << e << " 已存在于 " << x << std::endl;
		return x;
	}
	x = new BinNode<T>(e, this ->_hot, nullptr, nullptr, -1);
	std::cout << "创建元素 " << e << " 节点 " << x << std::endl;
	std::cout << "将元素 " << e << " 作为 " << this->_hot << " 的孩子插入" << std::endl;
	this ->_size++;
	printTree();
	solveDoubleRed(x);
	printTree();
	return x;
}

template<typename T>
inline bool RedBalckTree<T>::remove(const T& e)
{
	std::cout << std::endl;
	std::cout << "准备删除元素 " << e << std::endl;
	BinNodePosi(T)& x = this ->search(e);
	if (!x) {
		std::cout << "未找到待删除的元素 " << e << std::endl;
		printTree();
		return false;
	}

	BinNodePosi(T) r = this -> removeAt(x, this->_hot);
	if (--this->_size <= 0) {
		std::cout << "已删除最后一个节点，当前红黑树为空" << std::endl;
		printTree();
		return true;
	}

	if (!this ->_hot) {
		std::cout << "当前删除的是根节点,自动设置接替的元素颜色为【黑】" << std::endl;
		this->_root->color = RB_BLACK;
		updateHeight(this->_root);
		printTree();
		return true;
	}

	if (BlackHeightUpdated((*this->_hot))) {
		std::cout << "删除元素后,当前节点黑高度平稳,无需重构拓扑、重染色" << std::endl;
		printTree();
		return true;
	}

	if (IsRed(r)) {
		std::cout << "删除 " << e << " 后，接替的元素颜色为红，直接置【黑】,更新高度" << std::endl;
		r->color = RB_BLACK;
		r->height++;
		printTree();
		return true;
	}

	solveDoubleBlack(r);
	printTree();
	return true;
}

template<typename T>
void RedBalckTree<T>::printTree() {
	if (!this->_root) {
		std::cout << "树 " << this->_root << " 为空" << std::endl;
		return;
	}
	BinNodePosi(T) r = this->_root;
	Queue<BinNodePosi(T)> bn;
	bn.enqueue(r);
	int lastHeight = r->height;

	std::cout << std::endl;
	std::cout << "----------------------------------- 开始打印红黑树 -----------------------------------" << std::endl;
	while (!bn.empty()) {
		BinNodePosi(T) x = bn.dequeue();
		if (x->lChild) {
			bn.enqueue(x->lChild);
		}

		if (x->rChild) {
			bn.enqueue(x->rChild);
		}

		if (x->height != lastHeight) {
			lastHeight = x->height;
			std::cout << std::endl;
			std::cout << "----------------------------------- " << lastHeight << " -----------------------------------" << std::endl;
		}
		std::cout << "节点 " << x << " 高 " << x->height << ",值 " << x->data << " " << (x->color == RBColor::RB_BLACK ? "黑色" : "红色") << " 左孩子 " << x ->lChild << " 右孩子 " << x->rChild << " 父节点 " << x->parent << std::endl;
	}
	std::cout << std::endl;
}