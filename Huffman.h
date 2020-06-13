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
* 1.字符评率统计
* 2.构建字符树序列
* 3.根据字符频率,构建赫夫曼编码树
* 4.生成编码表(编码表加入eof结束标识)
* 5.压缩文本为二进制文件
* 6.解压缩二进制压缩文件
*/

typedef Vector<HuffmanTree<int>*> HuffmanForest;
typedef std::map<int, Bitmap>  HuffmanCodeTable;

/**
* 读取文本文件内容输出字符频率
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

//获取权重最小的树
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

//将树插入森林中
void appendTreeToForest(HuffmanForest& forest, HuffmanTree<int>* treePtr) {
	forest.insert(treePtr);
}

//构建赫夫曼编码树
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

//生成字符的huffman编码表
HuffmanCodeTable genHuffmanCodeTable(HuffmanCodeTable& codeTable, HuffmanTree<int>* tree) {
	if()
}