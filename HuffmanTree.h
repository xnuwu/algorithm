#pragma once
#include <stdexcept>
#include "BinTree.h"

template <typename T>
class HuffmanTree {
public:
	unsigned weight = 0;
	BinTree<T>* treePtr;
	HuffmanTree() : weight(0), treePtr(nullptr) {};

	HuffmanTree(T e, unsigned w) : weight(w) {
		treePtr = new BinTree<T>();
		treePtr -> insertAsRoot(e);
	};

	T getData() {
		if (treePtr) {
			return treePtr->root()->data;
		}

		throw std::runtime_error("HuffmanTree not initializtion");
	}

	int getWeight() {
		if (treePtr) {
			return weight;
		}

		throw std::runtime_error("HuffmanTree not initializtion, can't getWeight");
	}

	void updateWeight(int weight) {
		this->weight = weight;
	}
};