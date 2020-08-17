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
};

template<typename T>
inline void RedBalckTree<T>::solveDoubleBlack(BinNodePosi(T) r)
{
#ifdef DEBUG
	std::cout << "��ʼ����ڵ� " << r << " ˫�ڳ�ͻ" << std::endl;
#endif // DEBUG

	BinNodePosi(T) p = r ? r->parent : this ->_hot;
	if (!p) {
#ifdef DEBUG
		std::cout << "������ڵ�,����!" << std::endl;
#endif // DEBUG

		return;
	}
	BinNodePosi(T) s = r == p->lChild ? p->rChild : p->lChild;

	if (IsBlack(s)) {
		BinNodePosi(T) t = nullptr;
		if (HasLChild(*s) && s->lChild->color == RB_RED) t = s->lChild;
		if (HasRChild(*s) && s->rChild->color == RB_BLACK) t = s->rChild;
		if (t) {
#ifdef DEBUG
			std::cout << r << " ���ֵܽڵ� " << s << " �ĺ����к�ڵ� " << t << " ׼������3+4�ع���Ȼ����Ⱦɫ! " << std::endl;
#endif // DEBUG

			RBColor oldColor = p->color;
#ifdef DEBUG
			std::cout << "�ȼ�ס���ڵ� " << p << " ����ɫΪ " << oldColor << std::endl;
#endif // DEBUG

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
#ifdef DEBUG
			std::cout << r << " ���ֵܽڵ� " << s << " �ĺ��Ӷ��Ǻ�ɫ" << std::endl;
#endif // DEBUG

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
#ifdef DEBUG
		std::cout << r << " ���ֵܽڵ� " << s << " Ϊ��ɫ,׼��������Ⱦɫ����ת��Ȼ����˫�ڳ�ͻ" << std::endl;
#endif // DEBUG

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
#ifdef DEBUG
	std::cout << "׼����� " << x << " �Ƿ����˫���ͻ" << std::endl;
#endif // DEBUG

	if (IsRoot(*x)) {
#ifdef DEBUG
		std::cout << x << " Ϊ���ڵ�,ֱ���ú�,�������" << std::endl;
#endif // DEBUG

		x->color = RB_BLACK;
		x->height++;
		return;
	}
	BinNodePosi(T) p = x->parent;
	if (IsBlack(p)) {
#ifdef DEBUG
		std::cout << "�ڵ� " << x << " �ĸ��ڵ� " << p << " Ϊ��ɫ�ڵ�,������˫���ͻ,�������" << std::endl;
#endif // DEBUG

		return;
	}
#ifdef DEBUG
	std::cout << "�ڵ� " << x << " �ĸ��ڵ� " << p << " Ϊ��ɫ�ڵ�" << std::endl;
#endif // DEBUG


	BinNodePosi(T) g = p->parent;
	BinNodePosi(T) u = uncle(x);

#ifdef DEBUG

	std::cout << x << " ���游�ڵ� " << g << " Ԫ��ֵ " << g->data << " ��ɫ " << (g->color == RBColor::RB_BLACK ? "��ɫ" : "��ɫ") << std::endl;
	if (u) {
		std::cout << x << " ������ڵ� " << u << " Ԫ��ֵ " << u->data << " ��ɫ " << (u->color == RBColor::RB_BLACK ? "��ɫ" : "��ɫ") << std::endl;
	}
	else {
		std::cout << x << " ������ڵ�Ϊ��,Ĭ�Ϻ�ɫ" << std::endl;
	}

#endif // DEBUG

	if (IsBlack(u)) {
		
		if (IsLChild(*x) == IsLChild(*p)) {
			p->color = RB_BLACK;
		}
		else {
			x->color = RB_BLACK;
		}
		g->color = RB_RED;
		BinNodePosi(T) r = FromParentTo(*g) = this ->rotateAt(x);
#ifdef DEBUG
		std::cout << "��Ⱦɫ,Ȼ��3+4���� " << x << " �ڵ�" << std::endl;
#endif // DEBUG

	}
	else {
		p->color = RB_BLACK; p->height++;
		u->color = RB_BLACK; u->height++;
		if (!IsRoot(*g)) {
			g->color = RB_RED;
		}
#ifdef DEBUG
		std::cout << "��Ⱦɫ��,׼������游�ڵ� " << g << " �Ƿ����˫��" << std::endl;
#endif // DEBUG

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
#ifdef DEBUG
	std::cout << std::endl;
	std::cout << "׼������Ԫ�� " << e << std::endl;
#endif // DEBUG

	BinNodePosi(T)& x = this -> search(e);
	if (x) {
#ifdef DEBUG
		std::cout << "�������Ԫ�� " << e << " �Ѵ����� " << x << std::endl;
#endif // DEBUG

		return x;
	}
	x = new BinNode<T>(e, this ->_hot, nullptr, nullptr, -1);
#ifdef DEBUG
	std::cout << "����Ԫ�� " << e << " �ڵ� " << x << std::endl;
	std::cout << "��Ԫ�� " << e << " ��Ϊ " << this->_hot << " �ĺ��Ӳ���" << std::endl;
#endif // DEBUG

	this ->_size++;
	solveDoubleRed(x);
	return x;
}

template<typename T>
inline bool RedBalckTree<T>::remove(const T& e)
{
#ifdef DEBUG
	std::cout << std::endl;
	std::cout << "׼��ɾ��Ԫ�� " << e << std::endl;
#endif // DEBUG

	BinNodePosi(T)& x = this ->search(e);
	if (!x) {
#ifdef DEBUG
		std::cout << "δ�ҵ���ɾ����Ԫ�� " << e << std::endl;
#endif // DEBUG

		return false;
	}

	BinNodePosi(T) r = this -> removeAt(x, this->_hot);
	if (--this->_size <= 0) {
#ifdef DEBUG
		std::cout << "��ɾ�����һ���ڵ㣬��ǰ�����Ϊ��" << std::endl;
#endif // DEBUG

		return true;
	}

	if (!this ->_hot) {
#ifdef DEBUG
		std::cout << "��ǰɾ�����Ǹ��ڵ�,�Զ����ý����Ԫ����ɫΪ���ڡ�" << std::endl;
#endif // DEBUG

		this->_root->color = RB_BLACK;
		updateHeight(this->_root);
		return true;
	}

	if (BlackHeightUpdated((*this->_hot))) {
#ifdef DEBUG
		std::cout << "ɾ��Ԫ�غ�,��ǰ�ڵ�ڸ߶�ƽ��,�����ع����ˡ���Ⱦɫ" << std::endl;
#endif // DEBUG

		return true;
	}

	if (IsRed(r)) {
#ifdef DEBUG
		std::cout << "ɾ�� " << e << " �󣬽����Ԫ����ɫΪ�죬ֱ���á��ڡ�,���¸߶�" << std::endl;
#endif // DEBUG

		r->color = RB_BLACK;
		r->height++;
		return true;
	}

	solveDoubleBlack(r);
	return true;
}
