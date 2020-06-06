#pragma once
#include "Stack.h"

class ExpParen {
public:
	static void trim(const char exp[], int& lo, int& hi) {
		while (lo <= hi && (exp[lo] != '(' && exp[lo] != ')')) {
			lo++;
		}

		while (lo <= hi && (exp[hi] != ')' && exp[hi] != '(')) {
			hi--;
		}
	}

	static int devide(const char exp[], int& lo, int& hi) {
		int mi = lo;
		int crc = 1;

		while (0 < crc && (++mi <= hi)) {
			if (exp[mi] == '(') {
				crc++;
			}
			else if (exp[mi] == ')') {
				crc--;
			}
		}

		return mi;
	}

	static bool paren(const char exp[], int lo, int hi) {
		trim(exp, lo, hi);
		if (lo > hi) return true;
		if (exp[lo] == ')') return false;
		if (exp[hi] == '(') return false;
		int mi = devide(exp, lo, hi);
		if (mi > hi) return false;
		return paren(exp, lo + 1, mi - 1) && paren(exp, mi + 1, hi);
	}

	static bool paren(const char exp[]) {
		Stack<char> s;
		for (int i = 0; exp[i]; i++) {
			switch (exp[i])
			{
			case '(':
			case '[':
			case '{':
				s.push(exp[i]);
				break;
			case ')':
				if (s.empty() || s.pop() != '(') return false;
				break;
			case ']':
				if (s.empty() || s.pop() != '[') return false;
				break;
			case '}':
				if (s.empty() || s.pop() != '{') return false;
				break;
			default:
				break;
			}
		}
		return s.empty();
	}
};
