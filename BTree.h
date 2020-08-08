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

	void printTree();
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
		p->child.insert(pr + 2, nt);
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
	if (n->child.size() >= (_order + 1) / 2) {
		std::cout << "�ڵ� " << n << " ��" << n->child.size() << "�����ӣ�δ����" << std::endl;
		return;
	}

	std::cout << "�ڵ� " << n << " ��������Ϊ " << n->child.size() << ", ��ǰB����Ϊ" << _order << ",��ʼ��������" << std::endl;

	BTNodePosi(T) p = n->parent;

	//�ݹ��
	if (!p) {

		std::cout << "�ݹ鵽����ڵ�" << std::endl;
		if (!n->key.size() && n->child[0]) {

			std::cout << "���ڵ㵱ǰ����Ԫ��,���Ǹ��ڵ㺢�Ӵ���,���¸��ڵ�Ϊ���ӽڵ�" << std::endl;
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
		//���ڽ�λ
		if (ls->child.size() > (_order + 1) / 2) {

			std::cout << "�ڵ� " << n << " �Ӹ��ڵ� " << p << " ��Ԫ�� " << p->key[r] << std::endl;
			n->key.insert(0, p->key[r]);
			
			std::cout << "�ڵ� " << n << " ����ڵ� " << ls << " �躢�� " << ls->child[ls->child.size() - 1] << std::endl;
			n->child.insert(0, ls->child.remove(ls->child.size() - 1));

			std::cout << "���ڵ� " << p << " ������Ԫ�� " << ls << " ��Ԫ�� " << ls->key[ls->key.size() - 1] << std::endl;
			p->key[r] = ls->key[ls->key.size() - 1];

			ls->key.remove(ls->key.size() - 1);

			if (n->child[0]) {
				std::cout << n << " �޸Ĵ����ڽ�����ĺ��� " << n->child[0] << " �ĸ���Ϊ�Լ�" << std::endl;
				n->child[0]->parent = n;
			}
			return;
		}
	}

	if (r < p->child.size() - 1) {
		BTNodePosi(T) rs = p->child[r + 1];
		//���ڽ�λ
		if (rs->child.size() > (_order + 1) / 2) {

			std::cout << "�ڵ� " << n << " �Ӹ��ڵ� " << p <<" ��Ԫ�� "  << p->key[r] << std::endl;
			n->key.insert(p->key[r]);

			std::cout << "�ڵ� " << n << " ���ҽڵ� " << rs << " �躢�� " << rs->child[0] << std::endl;
			n->child.insert(rs->child.remove(0));

			std::cout << "���ڵ� " << p << " ������Ԫ�� " << rs << " ��Ԫ�� " << rs->key[0] << std::endl;
			p->key[r] = rs->key.remove(0);
			
			if (n->child[n->child.size() - 1]) {
				std::cout << n << " �޸Ĵ����ڽ�����ĺ��� " << n->child[n->child.size() - 1] << " �ĸ���Ϊ�Լ�" << std::endl;
				n->child[n->child.size() - 1]->parent = n;
			}
			return;
		}
	}

	if (r > 0) {
		std::cout << n << " ׼���Ӹ��׽�λԪ�� " << p->key[r-1] << " �����ھӺϲ�" << std::endl;
		BTNodePosi(T) ls = p->child[r - 1];
		
		std::cout << ls << " ��ӴӸ��׽�λ��Ԫ�� " << p->key[r - 1] << std::endl;
		ls->key.insert(p->key.remove(r-1));

		std::cout << n << " �ĸ���׼��ȥ����,��׼�������ϲ������ھ� " << ls << " ��" << std::endl;
		p->child.remove(r);

		while (n->key.size() > 0) {
			std::cout << "���� " << ls << " ������� " << n << " ��Ԫ�� " << n->key[0] << std::endl;
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
		std::cout << "�ͷŽڵ� " << n << std::endl;
		Cleaner<BTNodePosi(T)>::clean(n);
	}
	else {
		std::cout << n << " ׼���Ӹ��׽�λԪ�� " << p->key[r] << " �ϲ������ھ�" << std::endl;
		BTNodePosi(T) rs = p->child[r + 1];

		std::cout << n << " ��ӴӸ��׽�λ��Ԫ�� " << p->key[r] << std::endl;
		n->key.insert(p->key.remove(r));

		std::cout << rs << " �ĸ���׼��ȥ����,��׼������ڵ� " << n << " ��" << std::endl;
		p->child.remove(r + 1);

		while (rs->key.size() > 0) {
			std::cout << n << " ��������ҽڵ� " << rs << " ��Ԫ�� " << rs->key[0] << std::endl;
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
		std::cout << "�ͷŽڵ� " << rs << std::endl;
		Cleaner<BTNodePosi(T)>::clean(rs);
	}
	
	std::cout << "׼����鸸�� " << p << " �Ƿ��������" << std::endl;
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
	std::cout << _hot << " ���� " << e << std::endl;
	solveOverflow(_hot);
	printTree();
}

template<typename T>
inline bool BTree<T>::remove(const T& e)
{
	std::cout << "׼��ɾ�� " << e << std::endl;
	BTNodePosi(T) v = search(e);
	if (!v) {
		std::cout << "δ�ҵ���ɾ��Ԫ�� " << e << std::endl;
		return false;
	}

	Rank r = v->key.search(e);
	if (v->child[r+1]) {
		BTNodePosi(T) u = v->child[r + 1];
		while (u->child[0]) {
			u = u->child[0];
		}

		std::cout << "�����ڵ� " << u << " ����Ԫ��ֵ " << u->key[0] << " �� " << v << " �� " << r << " λ��,��ֵ " << v->key[r] << " ���� " << std::endl;
		v->key[r] = u->key[0];
		v = u;
		r = 0;
	}
	std::cout << "ɾ��λ�� " << v << " ��Ԫ�� " << v->key[r] << std::endl;
	v->key.remove(r);
	v->child.remove(r + 1); //Ҷ�ڵ㺢��Ϊ��,ֱ��ɾ��
	_size--;
	solveUnderflow(v);
	printTree();
}

template<typename T>
inline void BTree<T>::printTree()
{
	std::cout << "********************************************** ��ʼ **********************************************" << std::endl;

	if (!_root) {
		std::cout << "B�� " << _root << " Ϊ��" << std::endl;
	}
	else {
		Queue<BTNodePosi(T)> queue;
		queue.enqueue(_root);
		while (!queue.empty()) {

			std::cout << std::endl;
			BTNodePosi(T) n = queue.dequeue();
			std::cout << "�ڵ� " << n << " ��Ԫ��: ";
			for (int i = 0; i < n->key.size(); i++) {
				std::cout << n->key[i] << " ";
			}
			std::cout << std::endl;
			std::cout << "�ڵ� " << n << " �ĺ���: ";
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
	std::cout << "********************************************** ���� **********************************************" << std::endl;
	std::cout << std::endl;
}

