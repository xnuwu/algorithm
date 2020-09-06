#pragma once

template <typename T> 
class PQ {
public:
	virtual void insert(T) = 0;
	virtual T getMax() = 0;
	virtual T delMax() = 0;
};

