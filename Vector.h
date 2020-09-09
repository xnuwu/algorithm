#pragma once
#define VECTOR_DEFAULT_CAPCITY 10
#include "Release.h"
#include <random>
#include <iostream>

using std::uniform_int_distribution;
using std::default_random_engine;

typedef int Rank;

template <typename T> bool lt(T* a, T* b);
template <typename T> bool lt(T& a, T& b);
template <typename T> bool eq(T* a, T* b);
template <typename T> bool eq(T& a, T& b);

template <typename T> Rank binSearch(T* _elem, T e, Rank lo, Rank hi);

template <typename T>
class Vector
{
	/**************************************** 判等与比较 ****************************************/
	friend bool lt<T>(T* a, T* b);
	friend bool lt<T>(T& a, T& b);
	friend bool eq<T>(T* a, T* b);
	friend bool eq<T>(T& a, T& b);

	/**************************************** 查找算法 ****************************************/
	friend Rank binSearch<T>(T* _elem, T e, Rank lo, Rank hi);

protected:

	Rank _size;
	int _capacity;
	T* _elem;

	//复制数组区间
	void copyFrom(T const* A, Rank lo, Rank hi);

	//空间不足时扩容
	void expand();

	//装填因子过小时亚索
	void shrink();

	//扫描交换
	bool bubble(Rank lo, Rank hi);

	//起泡排序算法
	void bubbleSort(Rank lo, Rank hi);

	//选取最大元素
	Rank max(Rank lo, Rank hi);

	//选择排序算法
	void selectSort(Rank lo, Rank hi);

	//归并算法
	void merge(Rank lo, Rank mi, Rank hi);

	//归并排序
	void mergeSort(Rank lo, Rank hi);

	//轴点构造算法
	Rank partition(Rank lo, Rank hi);

	//快速排序算法
	void quickSort(Rank lo, Rank hi);

	//堆排序
	void heapSort(Rank lo, Rank hi);

	//交换
	void swap(T& a, T& b);

	//置乱器
	void permute(Vector<T>& v);

	//随机数
	int rand();

public:
	
	/**************************************** 构造函数 ****************************************/

	//容量c,规模s,默认值v
	Vector(int c = VECTOR_DEFAULT_CAPCITY, int s = 0, T v = 0) {
		_elem = new T[_capacity = c];
		for (_size = 0; _size < s; _elem[_size++] = v);
	}

	//数组区间复制
	Vector(T const* A, Rank lo, Rank hi) {
		copyFrom(A, lo, hi);
	}

	//数组整体复制
	Vector(T const* A, Rank n) {
		copyFrom(A, 0, n);
	}

	//向量区间复制
	Vector(Vector<T> const& v, Rank lo, Rank hi) {
		copyFrom(v._elem, lo, hi);
	}

	//向量整体复制
	Vector(Vector<T> const& v) {
		copyFrom(v._elem, 0, v._size);
	}

	/**************************************** 析构函数 ****************************************/

	~Vector() {
		delete[] _elem;
	}

	/**************************************** 公共方法 ****************************************/

	//规模
	Rank size() const {
		return _size;
	}

	//判空
	bool empty() const {
		return _size == 0;
	}

	//判断是否已经排序
	int disOrdered() const;

	//整体查找
	Rank find(T const& e) const {
		return find(e, 0, _size);
	}

	//区间查找未找到返回-1
	Rank find(T const& e, Rank lo, Rank hi) const;

	//整体查找
	Rank search(T const& e) const {
		return (0 >= _size ? -1 : binSearch(_elem, e, 0, _size));
	}

	//整体查找-未找到返回不大于e的最大的元素的下标
	Rank search(T const& e, Rank lo, Rank hi) const {
		return binSearch(_elem, e, lo, hi);
	}

	//数组下标访问
	T& operator[](Rank r) const;

	//重载赋值，进行克隆
	Vector<T>& operator=(Vector<T> const&);

	//删除秩谓r的元素
	T remove(Rank r);

	//删除秩区间元素
	int remove(Rank lo, Rank hi);

	//插入元素
	Rank insert(Rank r, T const& e);

	//末尾插入
	Rank insert(T const& e);

	//区间排序
	void sort(Rank lo, Rank hi);

	//整体排序
	void sort() {
		sort(0, _size);
	}

	//区间置乱
	void unsort(Rank lo, Rank hi);

	//整体置乱
	void unsort() {
		unsort(0, _size);
	}

	//无序去重
	int deduplicate();

	//有序去重
	int uniquify();

	//遍历(函数指针)
	void traverse(void (*)(T&));

	//遍历(函数对象）
	template <typename VST> void traverse(VST&);
};

template<typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi)
{
	_size = 0;
	_capacity = 2 * (hi - lo);
	_elem = new T[_capacity];
	while (lo < hi) {
		_elem[_size++] = A[lo++];
	}
}

template<typename T>
inline void Vector<T>::expand()
{
	if (_size < _capacity) return;
	if (_capacity < VECTOR_DEFAULT_CAPCITY) _capacity = VECTOR_DEFAULT_CAPCITY;
	T* _oldElem = _elem;
	_elem = new T[_capacity <<= 1];
	for (int i = 0; i < _size; i++) {
		_elem[i] = _oldElem[i];
	}
	if (_oldElem) {
		delete[] _oldElem;
	}
}

template<typename T>
inline void Vector<T>::shrink()
{
	if (_capacity < VECTOR_DEFAULT_CAPCITY << 1) return;
	if ((_size << 1) > _capacity) return;
	T* _oldElem = _elem;
	_elem = new T[_capacity >>= 1];
	for (int i = 0; i < _size; i++) {
		_elem[i] = _oldElem[i];
	}
	delete[] _oldElem;
}

template<typename T>
inline bool Vector<T>::bubble(Rank lo, Rank hi)
{
	bool sorted = false;
	while (++lo < hi) {
		if (_elem[lo - 1] > _elem[lo]) {
			sorted = false;
			swap(_elem[lo - 1], _elem[lo]);
		}
	}
	return sorted;
}

template<typename T>
inline void Vector<T>::bubbleSort(Rank lo, Rank hi)
{
	while (!bubble(lo, hi--));
}

template<typename T>
inline int Vector<T>::disOrdered() const
{
	int n = 0;
	for (int i = 1; i < _size; i++) {
		if (_elem[i - 1] > _elem[i]) {
			n++;
		}
	}
	return n;
}

template<typename T>
inline Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const
{
	while (lo < hi-- && _elem[hi] != e);
	return hi;
}

template<typename T>
inline T& Vector<T>::operator[](Rank r) const
{
	return _elem[r];
}

template<typename T>
inline Vector<T>& Vector<T>::operator=(Vector<T> const& v)
{
	if (_elem) {
		delete[] _elem;
	}
	copyFrom(v._elem, 0, v._size);
	return *this;
}

template<typename T>
inline T Vector<T>::remove(Rank r)
{
	T elem = _elem[r];
	remove(r, r + 1);
	return elem;
}

template<typename T>
inline int Vector<T>::remove(Rank lo, Rank hi)
{
	if (lo == hi) return 0;

	while (hi < _size) {
		Cleaner<T>::clean(_elem[lo]);
		_elem[lo++] = _elem[hi++];
	}
	_size = lo;
	shrink();
	return hi - lo;
}

template<typename T>
inline Rank Vector<T>::insert(Rank r, T const& e)
{
	expand();
	for (int i = _size; i > r; i--) {
		_elem[i] = _elem[i - 1];
	}
	_elem[r] = e;
	_size++;
	return r;
}

template<typename T>
inline Rank Vector<T>::insert(T const& e)
{
	return insert(_size, e);
}

template<typename T>
inline void Vector<T>::sort(Rank lo, Rank hi)
{
	static uniform_int_distribution<int> r(_capacity, 2 * _capacity);
	static default_random_engine engine;
	mergeSort(lo, hi);
	/*switch (r(engine))
	{
	case 1:
		bubbleSort(lo, hi);
		break;

	case 2:
		selectSort(lo, hi);
		break;

	case 3:
		mergeSort(lo, hi);
		break;

	case 4:
		heapSort(lo, hi);
		break;

	default:
		quickSort(lo, hi);
		break;
	}*/
}

template <typename T>
inline void Vector<T>::swap(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}

template<typename T>
inline void Vector<T>::permute(Vector<T>& v)
{
	for (int i = v._size; i > 0; i--) {
		swap(v[i - 1], v[rand() % i]);
	}
}

template<typename T>
inline int Vector<T>::rand()
{
	static uniform_int_distribution<int> r(_capacity, 2 * _capacity);
	static default_random_engine engine;
	return r(engine);
}

template<typename T>
inline void Vector<T>::unsort(Rank lo, Rank hi)
{
	T* v = _elem + lo;
	for (int i = hi - lo; i > 0; i--) {
		swap(v[i - 1], v[rand() % i]);
	}
}

template<typename T>
inline int Vector<T>::deduplicate()
{
	int oldSize = _size;
	for (int i = 1; i < _size;) {
		find(_elem[i], 0, i) != -1 ? remove(i) : i++;
	}
	return oldSize - _size;
}

template<typename T>
inline int Vector<T>::uniquify()
{
	int oldSize = _size;
	Rank r = 0;
	for (int i = 1; i < _size; i++) {
		if (_elem[i] != _elem[r]) {
			_elem[++r] = _elem[i];
		}
	}
	_size = r + 1;
	shrink();
	return oldSize - _size;
}

template<typename T>
inline void Vector<T>::traverse(void (*visit)(T&))
{
	for (int i = 0; i < _size; i++) {
		visit(_elem[i]);
	}
}

template<typename T>
template<typename VST>
inline void Vector<T>::traverse(VST& vst)
{
	for (int i = 0; i < _size; i++) {
		vst(_elem[i]);
	}
}

template <typename T>
inline bool lt(T* a, T* b)
{
	return lt(*a, *b);
}

template <typename T>
inline bool lt(T& a, T& b)
{
	return a < b;
}

template <typename T>
inline bool eq(T* a, T* b)
{
	return eq(*a, *b);
}

template <typename T>
inline bool eq(T& a, T& b)
{
	return a == b;
}

template <typename T>
inline Rank binSearch(T* _elem, T e, Rank lo, Rank hi)
{
	while (lo < hi) {
		Rank mi = (lo + hi) >> 1;
		(e < _elem[mi]) ? hi = mi : lo = mi + 1;
	}
	return --lo;
}

template<typename T>
inline void Vector<T>::merge(Rank lo, Rank mi, Rank hi)
{
	T* leftBegin = _elem + lo;
	int leftSize = mi - lo;
	T* leftData = new T[leftSize];
	for (Rank i = 0; i < leftSize; leftData[i] = leftBegin[i++]);

	int rightSize = hi - mi;
	T* rightBegin = _elem + mi;
	for (Rank i = 0, j = 0, k = 0; (j < leftSize) || (k < rightSize);) {
		if ((j < leftSize) && (!(k < rightSize) || (leftData[j] <= rightBegin[k] ))) {
			leftBegin[i++] = leftData[j++];
		}

		if ((k < rightSize) && (!(j < leftSize) || (leftData[j] > rightBegin[k]))) {
			leftBegin[i++] = rightBegin[k++];
		}
	}

	delete[] leftData;
}

template<typename T>
inline void Vector<T>::mergeSort(Rank lo, Rank hi)
{
	if (hi - lo < 2) return;
	Rank mi = (hi + lo) >> 1;
	mergeSort(lo, mi);
	mergeSort(mi, hi);
	merge(lo, mi, hi);
}
