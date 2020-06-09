#pragma once
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
#define FromParentTo(x) (IsRoot(x) ? _root : (IsLChild(x) ? (x).parent->lChild : (x).parent->rChild))

typedef enum
{
	RB_RED,
	RB_BLACK
} RBColor;

template <typename T>
class BinNode
{
public:
	BinNodePosi(T) parent;
	BinNodePosi(T) lChild;
	BinNodePosi(T) rChild;
	T data;
	int height;
	int size();

	BinNodePosi(T) insertAsLC(T const &e);
	BinNodePosi(T) insertAsRC(T const &e);

	BinNode() : height(0), parent(nullptr), lChild(nullptr), rChild(nullptr){};
	BinNode(T e, BinNodePosi(T) p = nullptr, BinNodePosi(T) l = nullptr, BinNodePosi(T) r = nullptr, int h = 0) : data(e), parent(p), lChild(l), rChild(r), height(h){};

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

	//比较器、判等器
	bool operator<(BinNode const &bn)
	{
		return data < bn.data;
	}

	bool operator=(BinNode const &bn)
	{
		return data == bn.data;
	}
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
