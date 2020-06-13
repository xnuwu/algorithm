#pragma once
#include <fstream>
#include <string>
#include <map>
#include <stdexcept>
#include <iostream>
#include "BinTree.h"
#include "Vector.h"
#include "HuffmanTree.h"
#include "Stack.h"
#include "Bitmap.h"

/*
* 1.�ַ�����ͳ��
* 2.�����ַ�������
* 3.�����ַ�Ƶ��,�����շ���������
* 4.���ɱ����(��������eof������ʶ)
* 5.ѹ���ı�Ϊ�������ļ�
* 6.��ѹ��������ѹ���ļ�
*/

typedef Vector<HuffmanTree<int>*> HuffmanForest;
typedef std::map<int, Bitmap>  HuffmanCodeTable;

/**
* ��ȡ�ı��ļ���������ַ�Ƶ��
*/
HuffmanForest readFileCharFrequency(const std::string& filename) {

	std::ifstream is(filename, std::ifstream::binary);
	std::map<int, unsigned> charFrequency;

	if (is) {
		char ch;
		while (!is.eof()) {
			is.get(ch);
			charFrequency[ch]++;
		}
	}
	else {
		throw std::runtime_error("can't read file " + filename);
	}
	charFrequency[EOF] = 1;

	HuffmanForest forest;
	for (std::map<int, unsigned>::iterator itr = charFrequency.begin(); itr != charFrequency.cend(); itr++) {
		HuffmanTree<int>* htp = new HuffmanTree<int>(itr->first, itr->second);
		forest.insert(htp);
	}
	return forest;
}

//��ȡȨ����С����
HuffmanTree<int>* removeMinWeightTree(HuffmanForest& forest) {
	if (forest.empty()) {
		throw std::runtime_error("HuffmanForest is empty, can't removeMinWeightTree");
	}
	int minIndex = 0;
	for (int i = 0; i < forest.size(); i++) {
		if (*(forest[i]) < *(forest[minIndex])) {
			minIndex = i;
		}
	}

	return forest.remove(minIndex);
}

//��������ɭ����
void appendTreeToForest(HuffmanForest& forest, HuffmanTree<int>* treePtr) {
	forest.insert(treePtr);
}

//�����շ���������
HuffmanTree<int>* buildHuffmanCodeTree(HuffmanForest& forest) {
	while (forest.size() > 1) {
		HuffmanTree<int>* minWeightTree = removeMinWeightTree(forest);
		HuffmanTree<int>* secondMinWeightTree = removeMinWeightTree(forest);
		HuffmanTree<int>* newTree = new HuffmanTree<int>('*', minWeightTree->getWeight() + secondMinWeightTree->getWeight());
		newTree-> treePtr -> attachAsLC(newTree -> treePtr -> root(), minWeightTree -> treePtr);
		newTree-> treePtr -> attachAsRC(newTree -> treePtr -> root(), minWeightTree -> treePtr);
		appendTreeToForest(forest, newTree);
	}

	return forest[0];
}

//�����ַ���huffman�����
HuffmanCodeTable genHuffmanCodeTable(HuffmanCodeTable& codeTable, HuffmanTree<int>* tree) {
	if()
}