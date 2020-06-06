#pragma once
#include "Stack.h"

class Convert {
public:
	static void convert(Stack<char>& s, int n, int base) {
		static char digit[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
		while (0 < n) {
			int reminder = (int)(n % base);
			s.push(digit[reminder]);
			n /= base;
		}
	}
};
