#pragma once
#include "ListNode.h"

template <typename T>
class List {

private:
	ListNodePos(T) header;
	ListNodePos(T) tailer;
	int _size;

protected:

	//列表初始化
	void init();

	//清除所有节点
	int clear();

	//赋值列表中自位置p起的n项
	void copyNodes(ListNodePos(T), int);

	//有序表区间归并
	void merge(ListNodePos(T)&, int, List<T>&, ListNodePos(T), int);

	//对从p开始连续的n个节点归并排序
	void mergeSort(ListNodePos(T)&, int);

	//对从p开始的连续n个节点选择排序
	void selectionSort(ListNodePos(T), int);

	//对从p开始的连续n个节点插入排序
	void insertSort(ListNodePos(T), int);

public:

	/****************************** 构造函数 ******************************/

	//默认
	List() { init(); }

	//整体复制L
	List(List<T> const& L);

	//复制L自第r项开始n项
	List(List<T> const& L, Rank r, int n);

	//复制p开始的n项
	List(ListNodePos(T) p, int n);

	/****************************** 析构 ******************************/

	//释放包含头尾哨兵在内的所有节点
	~List();

	/****************************** 只读访问接口 ******************************/
	
	//规模
	Rank size() const { return _size; }

	//判空
	bool empty() const { return _size <= 0; }

	//循秩访问
	T& operator[](Rank r) const;

	//首节点位置
	ListNodePos(T) first() const { return header->succ; }

	//末节点位置
	ListNodePos(T) last() const { return tailer-> pred; }

	//判断位置p是否对外合法i
	bool valid(ListNodePos(T) p) { return p && (tailer != p) && (header != p); }

	//判断列表是否已经排序
	int disOrdered() const;

	//无序列表查找
	ListNodePos(T) find(T const&) const { return find(e, _size, tailer); }

	//无序区间查找
	ListNodePos(T) find(T const& e, int n, ListNodePos(T) p) const;

	//有序列表查找
	ListNodePos(T) search(T const& e) const { return search(e, _size, tailer); }

	//有序区间查找
	ListNodePos(T) search(T const& e, int n, ListNodePos(T) p) const;

	//在p及其前n-1个后继中选出最大者
	ListNodePos(T) selectMax(ListNodePos(T) p, int n);

	//整体最大者
	ListNodePos(T) selectMax() { return selectMax(header->succ, _size); }

	/****************************** 可读写访问接口 ******************************/

	//将e当作首节点插入
	ListNodePos(T) insertAsFirst(T const& e);

	//将e当作末节点插入
	ListNodePos(T) insertAsLast(T const& e);

	//将e当作p的前驱插入
	ListNodePos(T) insertBefore(ListNodePos(T) p, T const& e);

	//将e当作p的后继插入
	ListNodePos(T) insertAfter(ListNodePos(T) p, T const& e);

	//删除合法位置p处的节点,返回被删除的节点
	T remove(ListNodePos(T) p);

	//全列表归并
	void merge(List<T>& L) { merge(first(), _size, L, L.first(), L._size); }

	//列表区间排序
	void sort(ListNodePos(T) p, int n);

	//列表整体排序
	void sort() { sort(first(), _size); }

	//无序去重
	int deduplicate();

	//有序去重
	int uniquify();

	//前后倒置
	void reverse();

	/****************************** 遍历 ******************************/

	//函数指针遍历，局部特性修改
	void traverse(void(*)(T&));

	//函数对象，全局性修改
	template <typename VST>
	void traverse(VST&);
};

template<typename T>
inline void List<T>::init()
{
	header = new ListNode<T>;
	tailer = new ListNode<T>;
	
	header->succ = tailer;
	header->pred = NULL;

	tailer->pred = header;
	tailer->succ = NULL;
	_size = 0;
}

template<typename T>
inline int List<T>::clear()
{
	int oldSize = _size;
	while (0 < _size) {
		remove(header->succ);
	}
	return oldSize；
}

template <typename T>
void List<T>::copyNodes(ListNodePos(T) p, int n) {
	init();
	while (n--)
	{
		insertAsLast(p->data);
		p = p->succ;
	}
}

template<typename T>
inline List<T>::List(List<T> const& L)
{
	copyNodes(L.header, L._size);
}

template<typename T>
inline List<T>::List(List<T> const& L, Rank r, int n)
{
	copyNodes(L[r], n);
}

template<typename T>
inline List<T>::List(ListNodePos(T) p, int n)
{
	copyNodes(p, n);
}

template<typename T>
inline List<T>::~List()
{
	clear();
	delete header;
	delete tailer;
}

template<typename T>
inline T& List<T>::operator[](Rank r) const
{
	ListNodePos(T) p = first();
	while (0 < r--)
	{
		p = p->succ;
	}
	return p->data;
}

template<typename T>
inline ListNodePos(T) List<T>::find(T const& e, int n, ListNodePos(T) p) const
{
	while (0 < n--) {
		if ((p = p->pred)->data == e) {
			return p;
		}
	}
	return NULL;
}

template<typename T>
inline ListNodePos(T) List<T>::insertAsFirst(T const& e)
{
	_size++;
	return header->insertAsSucc(e);
}

template<typename T>
inline ListNodePos(T) List<T>::insertAsLast(T const& e)
{
	_size++;
	return tailer->insertAsPred(e);
}

template<typename T>
inline ListNodePos(T) List<T>::insertBefore(ListNodePos(T) p, T const& e)
{
	_size++;
	return p->insertAsPred(e);
}

template<typename T>
inline ListNodePos(T) List<T>::insertAfter(ListNodePos(T) p, T const& e)
{
	_size++;
	return p->insertAsSucc(e);
}

template<typename T>
inline T List<T>::remove(ListNodePos(T) p)
{
	T e = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;
	_size--;
	return e;
}

template<typename T>
inline int List<T>::deduplicate()
{
	
}
