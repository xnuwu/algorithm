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
		std::cout << "��ʼ�������������ڵ� " << _root << std::endl;
	}

	~BTree() {
		if (_root) {
			std::cout << "�ͷ����ٶ����� " << _root << std::endl;
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
		std::cout << n << " �ڵ㺢��δ��,��" << n->child.size() << "��,B����Ϊ" << _order << std::endl;
		return;
	}
	std::cout << n << " �ڵ�����,��ʼ���� " << std::endl;

	//�������Ľڵ��±�
	Rank mid = _order / 2;
	
	BTNodePosi(T) nt = new BTNode<T>();
	std::cout << "�����½ڵ� " << nt << std::endl;
	//���һ��Ԫ���±�Ϊ_order - 1
	for (int i = 0; i < _order - 1 - mid; i++) {
		nt->key.insert(i, n->key.remove(mid + 1));
		nt->child.insert(i, n->child.remove(mid + 1));
		std::cout << "�½ڵ� " << nt << " λ�� " << i << " ���� "<< nt->key[i] << std::endl;
	}
	//���ұߺ���
	nt->child[_order - 1 - mid] = n->child.remove(mid + 1);

	std::cout << "�½ڵ㵱ǰ��" << nt->child.size() << "������," << nt->key.size() << "��Ԫ��"<< std::endl;
	for (int i = 0; i < nt->child.size(); i++) {
		if (nt->child[i]) {
			std::cout << "���� " << nt ->child[i] << " �ĸ���Ϊ " << nt << std::endl;
			nt->child[i]->parent = nt;
		}
	}
	T e = n->key.remove(mid);
	//�ϲ�����
	BTNodePosi(T) p = n->parent;
	if (p) {
		std::cout << "��Ԫ��" << e << "���� " << n << " �ĸ��ڵ�" << p << std::endl;
		Rank pr = p->key.search(e);
		p->key.insert(pr + 1, e);
		p->child.insert(pr + 1, nt);
		nt->parent = p;
		solveOverflow(p);
	}
	else {
		//���·�����ڵ�
		_root = new BTNode<T>(e, n, nt);
		std::cout << "��ǰΪ���ڵ���ѣ��������ɸ��ڵ� " << _root << " ���ڵ�ֵ " << e << " ���� " << n << " �Һ��� " << nt << std::endl;
	}
}

template<typename T>
inline void BTree<T>::solveUnderflow(BTNodePosi(T) n)
{
	if (n && n->child.size() >= (_order + 1) / 2) {
		std::cout << "�ڵ� " << n << " ��" << n->child.size() << "�����ӣ�δ����" << std::endl;
		return false;
	}

	std::cout << "�ڵ� " << n << " ��������Ϊ" << n->child.size() << ",��ʼ��������" << std::endl;

	BTNodePosi(T) p = n->parent;

	if (!p) {
		if (!n->key.size() && n->child[0]) {
			_root = n->child[0];
			_root->parent = nullptr;
			n->child[0] = nullptr;
			Cleaner<BTNodePosi(T)>::clean(n);
		}
		return;
	}

	//��������ڽڵ���������Ԫ��

	//��������ڽڵ���������Ԫ��

	//���ҽڵ㶼��������������ڽڵ㣬��ô�ϲ�

	//���ҽڵ㶼�������ұ������ڽڵ㣬��ô�ϲ�

	//�ϲ����鸸���������
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
	std::cout << _hot << " ���� " << e << std::endl;
	solveOverflow(_hot);
}

template<typename T>
inline bool BTree<T>::remove(const T& e)
{
	BTNodePosi(T) v = search(e);
	if (!v) {
		return false;
	}

	Rank r = v->key.search(e);
	if (v->child[0]) {
		//�������Ҷ�ڵ㣬��ô���̽ڵ㣨��ΪҶ�ڵ㣩����Ȼ��ɾ��
		BTNodePosi(T) u = v->child[r + 1];
		while (u->child[0]) {
			u = u->child[0];
		}
		v->key[r] = u->key[0];
		v = u;
		r = 0;
	}
	v->key.remove(r);
	v->child.remove(r + 1);
	_size--;
	solveUnderflow(v);
}

