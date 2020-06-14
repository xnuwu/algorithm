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
typedef std::map<int, std::string>  HuffmanCodeTable;

/**
* 读取文本文件内容输出字符频率
*/
HuffmanForest readFileCharFrequency(const std::string& filename) {

	std::ifstream is(filename, std::ifstream::binary);
	std::map<int, unsigned> charFrequency;

	if (is) {
		char ch;
		while (is.get(ch), !is.fail()) {
			charFrequency[(int)ch]++;
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
		if (forest[i]->getWeight() < forest[minIndex] -> getWeight()) {
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
		newTree-> treePtr -> attachAsRC(newTree -> treePtr -> root(), secondMinWeightTree -> treePtr);
		appendTreeToForest(forest, newTree);
	}

	return forest[0];
}

//生成字符的huffman编码表
void genHuffmanCodeTable(HuffmanCodeTable& codeTable, Bitmap& bitmap, int bitIndex, BinNode<int>* nodePtr) {
	if (IsLeaf(*nodePtr)) {
		codeTable.insert({nodePtr->data, bitmap.toString(bitIndex)});
		return;
	}

	if (HasLChild(*nodePtr)) {
		bitmap.clear(bitIndex);
		genHuffmanCodeTable(codeTable, bitmap, bitIndex + 1, nodePtr->lChild);
	}
	if (HasRChild(*nodePtr)) {
		bitmap.set(bitIndex);
		genHuffmanCodeTable(codeTable, bitmap, bitIndex + 1, nodePtr->rChild);
		bitmap.clear(bitIndex);
	}
}

std::string compressFile(HuffmanCodeTable& codeTable, const std::string& filename) {
	std::ifstream is(filename);
	Bitmap data;
	unsigned index = 0;

	if (is) {
		char ch;
		while (is.get(ch), !is.fail()) {
			std::string binString = codeTable[(int)ch];
			for (int i = 0; i < binString.size(); i++, index++) {
				if (binString[i] == '1') {
					data.set(index);
				}
				else {
					data.clear(index);
				}
			}
		}
		//EOF
		std::string binString = codeTable[EOF];
		for (int i = 0; i < binString.size(); i++, index++) {
			if (binString[i] == '1') {
				data.set(index);
			}
			else {
				data.clear(index);
			}
		}
		is.close();

		std::string compressedFilename = std::string(filename + ".huffmanBin");
		std::cout << "cData:" << data.toString(index) << std::endl;
		data.dump(compressedFilename);
		
		return compressedFilename;
	}
	else {
		throw std::runtime_error("compressFile failed, can't read file " + filename);
	}
}

std::string decompressFile(BinNode<int>* root, const std::string& compressedFilename) {
	std::ifstream is(compressedFilename, std::ifstream::binary | std::ifstream::ate);
	if (is) {
		std::string decompressedFile = compressedFilename + ".de";
		std::ofstream os(decompressedFile);

		is.seekg(0, std::ifstream::end);
		int filesize = is.tellg();
		Bitmap data(compressedFilename, filesize * 8);
		std::cout << "filesize:" << filesize << std::endl;
		std::cout << "dData:" << data.toString(filesize * 8) << std::endl;
		BinNode<int>* cursor = root;
		for (int i = 0; i < filesize * 8;) {
			if (cursor && IsLeaf(*cursor)) {
				if (cursor->data != EOF) {
					std::cout << (char)cursor->data;
					os << (char)cursor->data;
					cursor = root;
				}
				else {
					break;
				}
			}
			else if (data.test(i)) {
				i++;
				cursor = cursor->rChild;
			}
			else if (!data.test(i)) {
				i++;
				cursor = cursor->lChild;
			}
			else {
				std::cerr << "error bit " << i << std::endl;
			}
		}
		os.flush();
		os.close();
		return decompressedFile;
	}
	else {
		throw std::runtime_error("decompressFile failed, can't read file " + compressedFilename);
	}
}