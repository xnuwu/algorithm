#pragma once
#include "BST.h"

template <typename T>
class Splay : public BST<T> {
protected:
	void attachAsLChild(BinNodePosi(T) p, BinNodePosi(T) c);
	void attachAsRChild(BinNodePosi(T) p, BinNodePosi(T) c);
	BinNodePosi(T) splay(BinNodePosi(T) v);
public:
	BinNodePosi(T)& search(const T& e);
	BinNodePosi(T) insert(const T& e);
	bool remove(const T& e);
};

template<typename T>
inline void Splay<T>::attachAsLChild(BinNodePosi(T) p, BinNodePosi(T) c)
{
	p->lChild = c;

	if (c) {
		c->parent = p;
	}
}

template<typename T>
inline void Splay<T>::attachAsRChild(BinNodePosi(T) p, BinNodePosi(T) c)
{
	p->rChild = c;
	if (c) {
		c->parent = p;
	}
}

template<typename T>
inline BinNodePosi(T) Splay<T>::splay(BinNodePosi(T) v) {
	if (!v) {
		return nullptr;
	}

	BinNodePosi(T) g;
	BinNodePosi(T) p;
	
	while ((p = v->parnet) && (g = p->parent)) {
		BinNodePosi(T) gg = g->parent;
		if (IsLChild(*v)) {
			if (IsLChild(*p)) {	//zig-zig
				attachAsLChild(g, p->rChild);
				attachAsLChild(p, v->rChild);
				attachAsRChild(p, g);
				attachAsRChild(v, p);
			}
			else {	//zig-zag
				attachAsLChild(p, v->rChild);
				attachAsRChild(v, p);
				attachAsRChild(g, v->lChild);
				attachAsLChild(v, g);
			}
		}
		else {
			if (IsRChild(*p)) { //zag-zag
				attachAsRChild(g, p->lChild);
				attachAsRChild(p, v->lChild);
				attachAsLChild(p, g);
				attachAsLChild(v, p);
			}
			else { //zag-zig
				attachAsRChild(p, v->lChild);
				attachAsLChild(v, p);
				attachAsLChild(g, v->rChild);
				attachAsRChild(v, g);
			}
		}
		if (gg) {
			gg->lChild == g ? attachAsLChild(gg, v) : attachAsRChild(gg, v);
		}
		else {
			v->parent = nullptr;
		}

		this->updateHeight(g);
		this->updateHeight(p);
		this->updateHeight(v);
	}

	if (p = v->parent) {
		if (IsLChild(*v)) {
			attachAsLChild(p, v->rChild);
			attachAsRChild(v, p);
		}
		else {
			attachAsRChild(p, v->lChild);
			attachAsLChild(v, p);
		}
	}
	v->parent = nullptr;
	return v;
}

template<typename T>
inline BinNodePosi(T)& Splay<T>::search(const T& e)
{
	BinNodePosi(T) p = this -> searchIn(this->_root, e, this->_hot = nullptr);
	this -> _root = splay(p ? p : this->_hot);
	return this->_root;
}

template<typename T>
inline BinNodePosi(T) Splay<T>::insert(const T& e)
{
	
}

template<typename T>
inline bool Splay<T>::remove(const T& e)
{
	
}
