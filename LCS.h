#pragma once

#include <string>
#include <iostream>
#include <iomanip>

//最大公共子序列
class LCS
{
public:

	//递归法
	static std::string recursive(const char* A, int m, const char* B, int n);

	//迭代法
	static std::string iterate(const char* A, unsigned int m, const char* B, unsigned int n);
};

