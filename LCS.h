#pragma once

#include <string>
#include <iostream>
#include <iomanip>

//��󹫹�������
class LCS
{
public:

	//�ݹ鷨
	static std::string recursive(const char* A, int m, const char* B, int n);

	//������
	static std::string iterate(const char* A, unsigned int m, const char* B, unsigned int n);
};

