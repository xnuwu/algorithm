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

	//������������
	void copyFrom(T const* A, Rank lo, Rank hi);

	//�ռ䲻��ʱ����
	void expand();

	//װ�����ӹ�Сʱ����
	void shrink();

	//ɨ�轻��
	bool bubble(Rank lo, Rank hi);

	//���������㷨
	void bubbleSort(Rank lo, Rank hi);

	//ѡȡ���Ԫ��
	Rank max(Rank lo, Rank hi);

	//ѡ�������㷨
	void selectSort(Rank lo, Rank hi);

	//�鲢�㷨
	void merge(Rank lo, Rank mi, Rank hi);

	//�鲢����
	void mergeSort(Rank lo, Rank hi);

	//��㹹���㷨
	Rank partition(Rank lo, Rank hi);

	//���������㷨
	void quickSort(Rank lo, Rank hi);

	//������
	void heapSort(Rank lo, Rank hi);

	//����
	void swap(T& a, T& b);

	//������
	void permute(Vector<T>& v);

	//�����
	int rand();
public:
	
	/**************************************** ���캯�� ****************************************/

	//����c,��ģs,Ĭ��ֵv
	Vector(int c = VECTOR_DEFAULT_CAPCITY, int s = 0, T v = 0) {
		_elem = new T[_capacity = c];
		for (_size = 0; _size < s; _elem[_size++] = v);
	}

	//�������临��
	Vector(T const* A, Rank lo, Rank hi) {
		copyFrom(A, lo, hi);
	}

	//�������帴��
	Vector(T const* A, Rank n) {
		copyFrom(A, 0, n);
	}

	//�������临��
	Vector(Vector<T> const& v, Rank lo, Rank hi) {
		copyFrom(v._elem, lo, hi);
	}

	//�������帴��
	Vector(Vector<T> const& v) {
		copyFrom(v._elem, 0, v._size);
	}

	/**************************************** �������� ****************************************/

	~Vector() {
		delete[] _elem;
	}

	/**************************************** �������� ****************************************/

	//��ģ
	Rank size() const {
		return _size;
	}

	//�п�
	bool empty() const {
		return _size == 0;
	}

	//�ж��Ƿ��Ѿ�����
	int disOrdered() const;

	//�������
	Rank find(T const& e) const {
		return find(e, 0, _size);
	}

	//�������
	Rank find(T const& e, Rank lo, Rank hi) const;

	//�������
	Rank search(T const& e) const {
		return (0 >= _size ? -1 : search(e, 0, _size));
	}

	//�������
	Rank search(T const& e, Rank lo, Rank hi) const;

	//�����±����
	T& operator[](Rank r) const;

	//���ظ�ֵ�����п�¡
	Vector<T>& operator=(Vector<T> const&);

	//ɾ����νr��Ԫ��
	T remove(Rank r);

	//ɾ��������Ԫ��
	int remove(Rank lo, Rank hi);

	//����Ԫ��
	Rank insert(Rank r, T const& e);

	//ĩβ����
	Rank insert(T const& e);

	//��������
	void sort(Rank lo, Rank hi);

	//��������
	void sort() {
		sort(0, _size);
	}

	//��������
	void unsort(Rank lo, Rank hi);

	//��������
	void unsort() {
		unsort(0, _size);
	}

	//����ȥ��
	int deduplicate();

	//����ȥ��
	int uniquify();

	//����(����ָ��)
	void traverse(void (*)(T&));

	//����(��������
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
