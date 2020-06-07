#pragma once
#include "List.h"

template <typename T>
class Queue : public List<T> {
public:
	void enqueue(T const& e) {
		insertAsLast(e);
	}

	T dequeue() {
		remove(first());
	}

	T& front() {
		return first()->data;
	}
};