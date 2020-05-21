#pragma once

#define VECTOR_DEFAULT_CAPCITY 10

#include <random>

using std::uniform_int_distribution;
using std::default_random_engine;

typedef int Rank;
template <typename T>
class Vector
{
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

	//区间查找
	Rank find(T const& e, Rank lo, Rank hi) const;

	//整体查找
	Rank search(T const& e) const {
		return (0 >= _size ? -1 : search(e, 0, _size));
	}

	//区间查找
	Rank search(T const& e, Rank lo, Rank hi) const;

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
inline void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi)
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
	if (_elem < _capacity) return;
	if (_capacity < VECTOR_DEFAULT_CAPCITY) _capacity = VECTOR_DEFAULT_CAPCITY;
	T* _oldElem = _elem;
	_elem = new T[_capacity <<= 1];
	for (int i = 0; i < _size; i++) {
		_elem[i] = _oldElem[i];
	}
	delete[] _oldElem;
}

template<typename T>
inline void Vector<T>::shrink()
{
	if (_capacity < VECTOR_DEFAULT_CAPCITY << 1) return;
	if (_size << 1 > _capacity) return;
	T* _oldElem = _elem;
	_elem = new T[_capacity >>= 1];
	for (int i = 0; i < _size; i++) {
		_elem[i] = _oldElem[i];
	}
	delete[] _oldElem;
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

template <typename T>
inline void swap(T& a, T& b) {
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
	uniform_int_distribution<int> seed(_capacity, 2 * _capacity);
	default_random_engine e;
	return e(seed);
}

template<typename T>
inline void Vector<T>::unsort(Rank lo, Rank hi)
{
	T* v = _elem + lo;
	for (int i = hi - lo; i > 0; i--) {
		swap(v[i - 1], v[rand() % i]);
	}
}
