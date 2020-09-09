#pragma once
#include "PQ.h"
#include "Vector.h"

#define InHeap(n, i) (((-1) < (i)) || ((i) < (n)))
#define LChild(i) (((i) << 1) + 1)
#define RChild(i) (((i) + 1) << 1)
#define Parent(i) (((i) - 1) >> 1)
#define LastInternal(n) Parent((n) - 1)
#define ParentValid(n) ((n) > 0)
#define LChildValid(n,i) InHeap(n, LChild(i))
#define RChildValid(n,i) InHeap(n, RChild(i))
#define Bigger(PQ, i, j) (lt(PQ[i], PQ[j]) ? j : i)
#define ProperParent(PQ, n, i) (RChildValid(n,i) ? Bigger(PQ, Bigger(PQ, i, LChild(i)), RChild(i)) : (LChildValid(n,i) ? Bigger(PQ, i, LChild(i)) : i))


template<typename T>
class PQComplete : public PQ<T>, public Vector<T> {
protected:
	Rank precolateUp(Rank r);
	Rank precolateDown(Rank n, Rank r);
	void heapify(Rank r);
public:
	PQComplete() {};
	PQComplete(T* a, Rank n) {
		copyFrom(a, 0, n);
		heapify(n);
	};

	void insert(T t);
	T getMax();
	T delMax();
};

template<typename T>
inline Rank PQComplete<T>::precolateUp(Rank r)
{
	T e = this -> _elem[r];
	while (ParentValid(r)) {
		Rank p = Parent(r);
		if (lt(this->_elem[p], e)) {
			this -> _elem[r] = this ->_elem[p];
			r = p;
		}
		else {
			break;
		}
	}
	this->_elem[r] = e;
	return r;
}

template<typename T>
inline Rank PQComplete<T>::precolateDown(Rank n, Rank r)
{
	Rank j;
	T e = getMax();
	while (r != (j = ProperParent(this -> _elem, n, r))) {
		this ->_elem[r] = this->_elem[j];
		this->_elem[j] = e;
		r = j;
	}
	return r;
}

template<typename T>
inline void PQComplete<T>::heapify(Rank n)
{
	for (int i = LastInternal(n); InHeap(n, i); i--) {
		precolateDown(n, i);
	}
}

template<typename T>
inline void PQComplete<T>::insert(T e)
{
	Vector<T>::insert(e);
	precolateUp(this->_size - 1);
}

template<typename T>
inline T PQComplete<T>::getMax()
{
	return this->_elem[0];
}

template<typename T>
inline T PQComplete<T>::delMax()
{
	T e = this->_elem[0];
	this->_elem[0] = this->_elem[this->_size - 1];
	this->_size--;
	precolateDown(this -> _size, 0);
	return e;
}
