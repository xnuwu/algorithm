#pragma once
#include "ListNode.h"

template <typename T>
class List
{

private:
	ListNodePos(T) header;
	ListNodePos(T) tailer;
	int _size;

protected:
	//�б��ʼ��
	void init();

	//������нڵ�
	int clear();

	//��ֵ�б�����λ��p���n��
	void copyNodes(ListNodePos(T), int);

	//���������鲢
	void merge(ListNodePos(T) & p, int n, List<T> &L, ListNodePos(T) q, int m);

	//�Դ�p��ʼ������n���ڵ�鲢����
	void mergeSort(ListNodePos(T) &, int);

	//�Դ�p��ʼ������n���ڵ�ѡ������
	void selectionSort(ListNodePos(T), int);

	//�Դ�p��ʼ������n���ڵ��������
	void insertSort(ListNodePos(T), int);

public:
	/****************************** ���캯�� ******************************/

	//Ĭ��
	List() { init(); }

	//���帴��L
	List(List<T> const &L);

	//����L�Ե�r�ʼn��
	List(List<T> const &L, Rank r, int n);

	//����p��ʼ��n��
	List(ListNodePos(T) p, int n);

	/****************************** ���� ******************************/

	//�ͷŰ���ͷβ�ڱ����ڵ����нڵ�
	~List();

	/****************************** ֻ�����ʽӿ� ******************************/

	//��ģ
	Rank size() const { return _size; }

	//�п�
	bool empty() const { return _size <= 0; }

	//ѭ�ȷ���
	T &operator[](Rank r) const;

	//�׽ڵ�λ��
	ListNodePos(T) & first() const { return header->succ; }

	//ĩ�ڵ�λ��
	ListNodePos(T) & last() const { return tailer->pred; }

	//�ж�λ��p�Ƿ����Ϸ�i
	bool valid(ListNodePos(T) p) { return p && (tailer != p) && (header != p); }

	//�ж��б��Ƿ��Ѿ�����
	int disOrdered() const;

	//�����б����
	ListNodePos(T) find(T const &e) const { return find(e, _size, tailer); }

	//�����������
	ListNodePos(T) find(T const &e, int n, ListNodePos(T) p) const;

	//�����б����
	ListNodePos(T) search(T const &e) const { return search(e, _size, tailer); }

	//�����������
	ListNodePos(T) search(T const &e, int n, ListNodePos(T) p) const;

	//��p����ǰn-1�������ѡ�������
	ListNodePos(T) selectMax(ListNodePos(T) p, int n);

	//���������
	ListNodePos(T) selectMax() { return selectMax(header->succ, _size); }

	/****************************** �ɶ�д���ʽӿ� ******************************/

	//��e�����׽ڵ����
	ListNodePos(T) insertAsFirst(T const &e);

	//��e����ĩ�ڵ����
	ListNodePos(T) insertAsLast(T const &e);

	//��e����p��ǰ������
	ListNodePos(T) insertBefore(ListNodePos(T) p, T const &e);

	//��e����p�ĺ�̲���
	ListNodePos(T) insertAfter(ListNodePos(T) p, T const &e);

	//ɾ���Ϸ�λ��p���Ľڵ�,���ر�ɾ���Ľڵ�
	T remove(ListNodePos(T) p);

	//ȫ�б�鲢
	void merge(List<T> &L) { merge(first(), _size, L, L.first(), L._size); }

	//�б���������
	void sort(ListNodePos(T) p, int n);

	//�б���������
	void sort() { mergeSort(first(), _size); }

	//����ȥ��
	int deduplicate();

	//����ȥ��
	int uniquify();

	//ǰ����
	void reverse();

	/****************************** ���� ******************************/

	//����ָ��������ֲ������޸�
	void traverse(void (*)(T &));

	//��������ȫ�����޸�
	template <typename VST>
	void traverse(VST &);
};

template <typename T>
void List<T>::init()
{
	header = new ListNode<T>;
	tailer = new ListNode<T>;

	header->succ = tailer;
	header->pred = NULL;

	tailer->pred = header;
	tailer->succ = NULL;
	_size = 0;
}

template <typename T>
int List<T>::clear()
{
	int oldSize = _size;
	while (0 < _size)
	{
		remove(header->succ);
	}
	return oldSize;
}

template <typename T>
void List<T>::mergeSort(ListNodePos(T) & p, int n)
{
	if (n < 2)
	{
		return;
	}

	int m = n >> 1;
	ListNodePos(T) q = p;
	for (int i = 0; i < m; i++)
	{
		q = q->succ;
	}
	mergeSort(p, m);
	mergeSort(q, n - m);
	merge(p, m, *this, q, n - m);
}

template <typename T>
void List<T>::merge(ListNodePos(T) & p, int n, List<T> &L, ListNodePos(T) q, int m)
{
	ListNodePos(T) tp = p;
	ListNodePos(T) pp = tp->pred;
	while (0 < m)
	{
		if ((0 < n) && (tp->data <= q->data))
		{
			if (q == (tp = tp->succ))
			{
				break;
			}
			n--;
		}
		else
		{
			insertBefore(tp, L.remove((q = q->succ)->pred));
			m--;
		}
	}
	p = pp->succ;
}

template <typename T>
void List<T>::copyNodes(ListNodePos(T) p, int n)
{
	init();
	while (n--)
	{
		insertAsLast(p->data);
		p = p->succ;
	}
}

template <typename T>
void List<T>::insertSort(ListNodePos(T) p, int n)
{
	for (int r = 0; r < n; r++)
	{
		insertAfter(search(p->data, r, p), p->data);
		p = p->succ;
		remove(p->pred);
	}
}

template <typename T>
void List<T>::selectionSort(ListNodePos(T) p, int n)
{
	ListNodePos(T) head = p->pred;
	ListNodePos(T) tail = p;
	for (int i = 0; i < n; i++)
	{
		tail = tail->succ;
	}

	while (1 < n)
	{
		ListNodePos(T) max = selectMax(head->succ, n);
		insertBefore(tail, remove(max));
		tail = tail->pred;
		n--;
	}
}

template <typename T>
List<T>::List(List<T> const &L)
{
	copyNodes(L.header, L._size);
}

template <typename T>
List<T>::List(List<T> const &L, Rank r, int n)
{
	copyNodes(L[r], n);
}

template <typename T>
List<T>::List(ListNodePos(T) p, int n)
{
	copyNodes(p, n);
}

template <typename T>
List<T>::~List()
{
	clear();
	delete header;
	delete tailer;
}

template <typename T>
T &List<T>::operator[](Rank r) const
{
	ListNodePos(T) p = first();
	while (0 < r--)
	{
		p = p->succ;
	}
	return p->data;
}

template <typename T>
int List<T>::disOrdered() const
{
	int cnt = 0;
	if (_size < 2)
	{
		return cnt;
	}

	ListNodePos(T) pre = header->succ;
	ListNodePos(T) curr = pre->succ;

	int index = 1;
	while (index++ < _size)
	{
		if (pre->data > curr->data)
		{
			cnt++;
		}
		pre = curr;
		curr = curr->succ;
	}

	return cnt;
}

template <typename T>
ListNodePos(T) List<T>::find(T const &e, int n, ListNodePos(T) p) const
{
	while (0 < n--)
	{
		if ((p = p->pred)->data == e)
		{
			return p;
		}
	}
	return NULL;
}

template <typename T>
ListNodePos(T) List<T>::search(T const &e, int n, ListNodePos(T) p) const
{
	//=����δ�ҵ�������·���header�ڵ�
	while (0 <= n--)
	{
		if ((p = p->pred)->data <= e)
		{
			break;
		}
	}
	return p;
}

template <typename T>
ListNodePos(T) List<T>::selectMax(ListNodePos(T) p, int n)
{
	ListNodePos(T) max = p;
	while (0 < --n)
	{
		if ((p = p->succ)->data >= max->data)
		{
			max = p;
		}
	}

	return max;
}

template <typename T>
ListNodePos(T) List<T>::insertAsFirst(T const &e)
{
	_size++;
	return header->insertAsSucc(e);
}

template <typename T>
ListNodePos(T) List<T>::insertAsLast(T const &e)
{
	_size++;
	return tailer->insertAsPred(e);
}

template <typename T>
ListNodePos(T) List<T>::insertBefore(ListNodePos(T) p, T const &e)
{
	_size++;
	return p->insertAsPred(e);
}

template <typename T>
ListNodePos(T) List<T>::insertAfter(ListNodePos(T) p, T const &e)
{
	_size++;
	return p->insertAsSucc(e);
}

template <typename T>
T List<T>::remove(ListNodePos(T) p)
{
	T e = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;
	_size--;
	return e;
}

template <typename T>
int List<T>::deduplicate()
{
	if (_size < 2)
	{
		return 0;
	}

	int oldSize = _size;
	ListNodePos(T) curr = first();
	int index = 1;
	while ((curr = curr->succ) != tailer)
	{
		ListNodePos(T) p = find(curr->data, index, curr);
		p ? remove(p) : index++;
	}

	return oldSize - _size;
}

template <typename T>
int List<T>::uniquify()
{
	if (_size < 2)
	{
		return 0;
	}

	int oldSize = _size;
	ListNodePos(T) curr = first();
	while (curr->succ != tailer)
	{
		if (curr->data != curr->succ->data)
		{
			curr = curr->succ;
		}
		else
		{
			remove(curr->succ);
		}
	}
	return _size - oldSize;
}

template <typename T>
void List<T>::traverse(void (*fn)(T &))
{
	ListNodePos(T) pos = header;
	while ((pos = pos->succ) != tailer)
	{
		fn(pos->data);
	}
}

template <typename T>
template <typename VST>
void List<T>::traverse(VST &visit)
{
	ListNodePos(T) pos = header;
	while ((pos = pos->succ) != tailer)
	{
		visit(pos->data);
	}
}