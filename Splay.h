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
	
	while ((p = v->parent) && (g = p->parent)) {
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
	if (!this->_root) {
		this->_size++;
		return this->_root = new BinNode<T>(e);
	}

	BinNodePosi(T) r = search(e);
	if (r->data == e) {
		return this->_root;
	}

	this->_size++;
	BinNodePosi(T) t = new BinNode<T>(e);
	if (r->data < e) {
		attachAsRChild(t, r->rChild);
		attachAsLChild(t, r);
	}
	else {
		attachAsLChild(t, r->lChild);
		attachAsRChild(t, r);
	}
	this->updateHeight(t);
	return this->_root = t;
}

template<typename T>
inline bool Splay<T>::remove(const T& e)
{
	if (!this->_root) {
		return false;
	}

	BinNodePosi(T) r = search(e);
	if (r->data != e) {
		return false;
	}
	else {
		BinNodePosi(T) newRoot = r->succ();
		if (newRoot == this->_root->rChild) {
			attachAsLChild(newRoot, this->_root->lChild);
		}
		else {
			newRoot->parent->lChild = nullptr;
			attachAsLChild(newRoot, this->_root->lChild);
			attachAsRChild(newRoot, this->_root->rChild);
		}
	}
	Cleaner<T>::clean(r->data);
	Cleaner<BinNodePosi(T)>::clean(r);
	this->updateHeightAbove(this->_hot);
	return true;
}
