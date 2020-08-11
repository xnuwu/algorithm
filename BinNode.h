#pragma once
#include "Queue.h"
#include "Stack.h"

#define BinNodePosi(T) BinNode<T> *
#define stature(p) ((p) ? (p)->height : -1)
#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && ((&x) == (x).parent->lChild))
#define IsRChild(x) (!IsRoot(x) && ((&x) == (x).parent->rChild))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lChild)
#define HasRChild(x) ((x).rChild)
#define HasChild(x) (HasLChild(x) || HasRChild(x))
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))
#define IsLeaf(x) (!HasChild(x))
#define sibling(p) (IsLChild(p) ? (p)->parent->rChild : (p)->parent->lChild)
#define uncle(p) (*(IsLChild(p->parent)) ? (p)->parent->parent->rChild : (p)->parent->parent->lChild)
#define FromParentTo(x) (IsRoot(x) ? (this ->_root) : (IsLChild(x) ? (x).parent->lChild : (x).parent->rChild))

typedef enum
{
	RB_RED,
	RB_BLACK
} RBColor;

template <typename T>
class BinNode
{
	//比较器、判等器
	friend bool operator<(const BinNode<T>& lbn, const BinNode<T>& rbn)
	{
		return lbn.data < rbn.data;
	};

	friend bool operator>(const BinNode<T>& lbn, const BinNode<T>& rbn)
	{
		return lbn.data > rbn.data;
	};

	friend bool operator==(const BinNode<T>& lbn, const BinNode<T>& rbn)
	{
		return lbn.data == rbn.data;
	};

public:
	BinNodePosi(T) parent;
	BinNodePosi(T) lChild;
	BinNodePosi(T) rChild;
	T data;
	int height;
	int deep;
	RBColor color;
	int size();

	BinNodePosi(T) insertAsLC(T const &e);
	BinNodePosi(T) insertAsRC(T const &e);

	BinNode() : height(0), parent(nullptr), lChild(nullptr), rChild(nullptr) {};
	BinNode(T e, BinNodePosi(T) p = nullptr, BinNodePosi(T) l = nullptr, BinNodePosi(T) r = nullptr, int h = 0, RBColor c = RB_RED) : data(e), parent(p), lChild(l), rChild(r), height(h), color(c) {};

	BinNode<T>& operator=(const BinNode<T> rbn) const {
		if (this != &rbn) {
			this->data = rbn.data;
			this->height = rbn.height;
			this->color = rbn.color;
			this->parent = rbn.parent;
			this->lChild = rbn.lChild;
			this->rChild = rbn.rChild;
		}
		return *this;
	}

	BinNode<T>& operator=(const BinNode<T> &&rbn) {
		if (this != &rbn) {
			this->data = rbn.data;
			this->height = rbn.height;
			this->color = rbn.color;
			this->parent = rbn.parent;
			this->lChild = rbn.lChild;
			this->rChild = rbn.rChild;
			rbn.height = 0;
			rbn.color = RB_RED;
			rbn.parent = nullptr;
			rbn.lChild = nullptr;
			rbn.rChild = nullptr;
		}
		return *this;
	}

	//生成每个节点的深度
	void updateDeep();

	//当前节点的直接后继(中序遍历)
	BinNodePosi(T) succ();

	//子树层级遍历
	template <typename VST>
	void travLevel(VST &);

	//子树先序遍历
	template <typename VST>
	void travPre(VST&);

	template <typename VST>
	void travPreR(BinNodePosi(T) p, VST& visit);

	template <typename VST>
	void visitAlongLeftBranch(BinNodePosi(T) p, VST& visit, Stack<BinNodePosi(T)>& s);

	template <typename VST>
	void travPreI2(BinNodePosi(T) p, VST& visit);

	//子树中序遍历
	template <typename VST>
	void travIn(VST&);

	template <typename VST>
	void travInR(BinNodePosi(T) p, VST& visit);

	void goAlongLeftBranch(BinNodePosi(T) p, Stack<BinNodePosi(T)>& s);

	template <typename VST>
	void travInI1(BinNodePosi(T) p, VST& visit);

	template <typename VST>
	void travInI2(BinNodePosi(T) p, VST& visit);

	template <typename VST>
	void travInI3(BinNodePosi(T) p, VST& visit);

	//子树后序遍历
	template <typename VST>
	void travPost(VST &);

	template <typename VST>
	void travPostR(BinNodePosi(T) p, VST& visit);

	//到达最高左侧可见叶节点,并将经过的节点按次序入栈
	void goToHLVFL(Stack<BinNodePosi(T)>& s);

	template <typename VST>
	void travPostI(BinNodePosi(T) p, VST& visit);
};

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsLC(T const &e)
{
	return lChild = new BinNode(e, this);
}

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsRC(T const &e)
{
	return rChild = new BinNode(e, this);
}

template<typename T>
inline void BinNode<T>::updateDeep()
{
	if (!this->parent) {
		this->deep = 0;
	}
	else {
		this->deep = this->parent->deep + 1;
	}
	if (this->lChild) {
		this->lChild->updateDeep();
	}
	if (this->rChild) {
		this->rChild->updateDeep();
	}
}

template<typename T>
BinNodePosi(T) BinNode<T>::succ()
{
	BinNodePosi(T) s = this;
	if (HasRChild(*s)) {
		s = rChild;
		while (HasLChild(*s)) {
			s = s->lChild;
		}
	}
	else {
		while (IsRChild(*s)) {
			s = s->parent;
		}
		s = s->parent;
	}
	return s;
}

template <typename T>
int BinNode<T>::size()
{
	int s = 1;
	if (lChild)
	{
		s += lChild->size();
	}

	if (rChild)
	{
		s += rChild->size();
	}

	return s;
}

template<typename T>
template<typename VST>
void BinNode<T>::travLevel(VST& visit)
{
	Queue<BinNodePosi(T)> queue;
	queue.enqueue(this);
	while (!queue.empty()) {
		BinNodePosi(T) p = queue.dequeue();
		visit(p->data);
		if (HasLChild(*p)) {
			queue.enqueue(p->lChild);
		}

		if (HasRChild(*p)) {
			queue.enqueue(p->rChild);
		}
	}
}

template<typename T>
template<typename VST>
void BinNode<T>::travPreR(BinNodePosi(T) p, VST& visit)
{
	if (!p) {
		return;
	}

	visit(p->data);
	travPreR(p->lChild, visit);
	travPreR(p->rChild, visit);
}

template<typename T>
template<typename VST>
void BinNode<T>::visitAlongLeftBranch(BinNodePosi(T) p, VST& visit, Stack<BinNodePosi(T)>& s)
{
	while (p) {
		visit(p->data);
		s.push(p->rChild);
		p = p->lChild;
	}
}

template<typename T>
template<typename VST>
void BinNode<T>::travPreI2(BinNodePosi(T) p, VST& visit)
{
	Stack<BinNodePosi(T)> s;
	while (true) {
		visitAlongLeftBranch(p, visit, s);
		
		if (s.empty()) break;
		p = s.pop();
	}
}

template<typename T>
template<typename VST>
void BinNode<T>::travInR(BinNodePosi(T) p, VST& visit)
{
	if (!p) {
		return;
	}

	travInR(p->lChild, visit);
	visit(p->data);
	travInR(p->rChild, visit);
}

template<typename T>
void BinNode<T>::goAlongLeftBranch(BinNodePosi(T) p, Stack<BinNodePosi(T)>& s)
{
	while (p) {
		s.push(p);
		p = p->lChild;
	}
}

template<typename T>
template<typename VST>
void BinNode<T>::travInI1(BinNodePosi(T) p, VST& visit)
{
	Stack<BinNodePosi(T)> s;
	while (true) {
		goAlongLeftBranch(p, s);
		if (s.empty()) break;

		p = s.pop();
		visit(p->data);
		p = p->rChild;
	}
}

template<typename T>
template<typename VST>
void BinNode<T>::travInI2(BinNodePosi(T) p, VST& visit)
{
	Stack<BinNodePosi(T)> s;
	while (true) {
		if (p) {
			s.push(p);
			p = p->lChild;
		}
		else if (!s.empty()) {
			p = s.pop();
			visit(p->data);
			p = p->rChild;
		}
		else {
			break;
		}
	}
}

template<typename T>
template<typename VST>
void BinNode<T>::travInI3(BinNodePosi(T) p, VST& visit)
{
	bool backtrack = false;
	while (true) {
		if (!backtrack && HasLChild(*p)) {
			p = p->lChild;
		}
		else {
			visit(p -> data);
			if (HasRChild(*p)) {
				p = p->rChild;
				backtrack = false;
			}
			else {
				if (!(p = p->succ())) break;
				backtrack = true;
			}
		}
	}
}

template<typename T>
template<typename VST>
void BinNode<T>::travPostR(BinNodePosi(T) p, VST& visit)
{
	if (!p) {
		return;
	}

	travPostR(p->lChild, visit);
	travPostR(p->rChild, visit);
	visit(p->data);
}

template<typename T>
void BinNode<T>::goToHLVFL(Stack<BinNodePosi(T)>& s)
{
	while (BinNodePosi(T) p = s.top()) {
		if (HasLChild(*p)) {
			if (HasRChild(*p)) {
				s.push(p->rChild);
			}
			s.push(p->lChild);
		}
		else {
			s.push(p->rChild);
		}
	}
	s.pop();
}

template<typename T>
template<typename VST>
inline void BinNode<T>::travPostI(BinNodePosi(T) x, VST& visit)
{
	Stack<BinNodePosi(T)> s;
	if (x) {
		s.push(x);
	}
	
	while (!s.empty())
	{
		if (s.top() != x -> parent) {
			goToHLVFL(s);
		}
		x = s.pop();
		visit(x->data);
	}
}
