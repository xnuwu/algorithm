#include "Fibonacci.h"

long Fibonacci::memoization(int num)
{
	if (num <= 0) {
		return 0;
	}

	int* mem = new int[num + 1];
	for (int i = 0; i < num + 1; i++) {
		mem[i] = -1;
	}
	return fib(num, mem);
}

long Fibonacci::fib(int num, int* mem)
{
	if (mem[num] != -1) {
		return mem[num];
	}
	if (num <= 2) {
		mem[num] = 1;
	}
	else {
		mem[num] = fib(num - 1, mem) + fib(num - 2, mem);
	}

	return mem[num];
}

