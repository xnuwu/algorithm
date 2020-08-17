#pragma once
#include "BST.h"
#include <algorithm>
#include <cstdio>
#include <malloc.h>

template<typename T>
class TreePrinter {
public:
	long maxDepth(BinNodePosi(T) n);
	void fillMap(BinNodePosi(T)* map, BinNodePosi(T) n, long index);
	int printNode(BinNodePosi(T) n, int w);
	void printTree(BinNodePosi(T) n);
};

template<typename T>
inline long TreePrinter<T>::maxDepth(BinNodePosi(T) n)
{
	if (!n) {
		return 0;
	}
	else {
		return std::max(maxDepth(n->lChild), maxDepth(n->rChild)) + 1;
	}
}

template<typename T>
void TreePrinter<T>::fillMap(BinNodePosi(T)* map, BinNodePosi(T) n, long index) {
	int i;
	map[index] = n;
	if (n) {
		fillMap(map, n->lChild, index * 2 + 1);
		fillMap(map, n->rChild, index * 2 + 2);
	}
}

void putchars(char c, int n) {
	while (n--)
		std::cout << c;
}

template<typename T>
int TreePrinter<T>::printNode(BinNodePosi(T) n, int w) {
	if (n) {
		if (n->color == RBColor::RB_BLACK)
			return printf("%*d-ºÚ", w, n->data);
		else
			return printf("%*d-ºì", w, n->data);
	}
	else {
		return printf("%*c¿Õ", w, ' ');
	}
}

void printLeftToParentBranchTop(int w) {
	printf("%*c", w + 1, ' ');
	putchars('_', w - 3);
	printf("/ ");
}

void printRightToParentBranchTop(int w) {
	putchar('\\');
	putchars('_', w - 3);
	printf("%*c", w + 2, ' ');
}

void printLeftToParentBranchBottom(int w) {
	printf("%*c%*c", w + 1, '/', w - 1, ' ');
}

void printRightToParentBranchBottom(int w) {
	printf("%*c%*c", w - 1, '\\', w + 1, ' ');
}

template<typename T>
void TreePrinter<T>::printTree(BinNodePosi(T) n) {
	long depth = maxDepth(n), i, j, index;
	BinNodePosi(T)* map = new BinNodePosi(T)[1 << depth + 1];
	for (int i = 0; i < 1 << depth + 1; i++) {
		map[i] = nullptr;
	}
	fillMap(map, n, 0);

	for (j = 0, index = 0; j < depth; j++) {
		int w = 1 << (depth - j + 1);
		if (j > 0) {
			// Top part of node to parent branch
			for (i = 0; i < 1 << j; i++)
				if (map[index + i])
					if (i % 2 == 0) printLeftToParentBranchTop(w);
					else            printRightToParentBranchTop(w);
				else
					putchars(' ', w * 2);
			putchar('\n');
			// Bottom part of node to parent branch
			for (i = 0; i < 1 << j; i++)
				if (map[index + i])
					if (i % 2 == 0) printLeftToParentBranchBottom(w);
					else            printRightToParentBranchBottom(w);
				else
					putchars(' ', w * 2);
			putchar('\n');
		}
		for (i = 0; i < 1 << j; i++, index++)
			if (map[index])
				putchars(' ', w * 2 - printNode(map[index], w));
			else
				putchars(' ', w * 2);
		putchar('\n');
	}

	free(map);
}