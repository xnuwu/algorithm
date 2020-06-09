#include "LCS.h"

std::string LCS::recursive(const char* A, int m, const char* B, int n)
{
	if (m < 0 || n < 0) {
		return "";
	}
	else if (A[m] == B[n]) {
		return recursive(A, m - 1, B, n - 1) + A[m];
	}
	else {
		std::string leftLcs = recursive(A, m - 1, B, n);
		std::string rightLcs = recursive(A, m, B, n - 1);
		return leftLcs.size() > rightLcs.size() ? leftLcs : rightLcs;
	}
}

std::string LCS::iterate(const char* A, unsigned int m, const char* B, unsigned int n)
{
	unsigned int lastX = 0;
	unsigned int lastY = 0;
	char* ret = new char[m > n ? m + 1 : n + 1];
	unsigned int cnt = 0;

	//迭代查找子序列
	for (unsigned int i = 0; i < m; i++) {
		for (unsigned int j = 0; j < n; j++) {
			if (A[i] == B[j] && j > lastX && i > lastY) {
				lastX = j;
				lastY = i;
				ret[cnt++] = A[i];
			}
		}
	}
	ret[cnt] = '\0';
	return std::string(ret);
}
