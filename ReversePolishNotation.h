#pragma once
#include "Stack.h"

#define N_OPTR 9
typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE} Operator;

const char pri[N_OPTR][N_OPTR] = {
	//运算符优先等级 [栈顶] [当前]
/* |-------------- 当前运算符 --------------| */
		 /* +    -    *    /    ^    !    (    )   \0  */
/* -- + */ '>', '>', '<', '<', '<', '<', '<', '>', '>',
/* |  - */ '>', '>', '<', '<', '<', '<', '<', '>', '>',
/* 栈 * */ '>', '>', '>', '>', '<', '<', '<', '>', '>',
/* 顶 / */ '>', '>', '>', '>', '<', '<', '<', '>', '>',
/* 运 ^ */ '>', '>', '>', '>', '>', '<', '<', '>', '>',
/* 算 ! */ '>', '>', '>', '>', '>', '>', ' ', '>', '>',
/* 符 ( */ '<', '<', '<', '<', '<', '<', '<', '=', ' ',
/* |  ) */ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
/*-- \0 */ '<', '<', '<', '<', '<', '<', '<', ' ', '='
};

//读取整数、小数
void readNumber(char*& S, Stack<double>& opNum) {
	double number = atof(S);
	int ch = *S;
	while(isdigit(ch) || ch == '.') {
		S++;
		ch = *S;
	}
	opNum.push(number);
}

//将数字添加到rpn后
void append(char*& rpn, double num) {
	char buff[128];
	if (0 < num - (int)num) {
		sprintf(buff, "%f \0", num);
	}
	else {
		sprintf(buff, "%d \0", (int)num);
	}
	char *newRpn = (char*) realloc(rpn, sizeof(char) * (strlen(rpn) + strlen(buff) + 1));
	if (newRpn) {
		rpn = newRpn;
		strcat(rpn, buff);
	}
	else {
		throw std::runtime_error("realloc mem failed");
	}
}

//将操作符添加到rpn后
void append(char*& rpn, char op) {
	char buff[3] = { op, ' ', '\0' };
	char* newRpn = (char*)realloc(rpn, sizeof(char) * (strlen(rpn) + 3));
	if (newRpn) {
		rpn = newRpn;
		strcat(rpn, buff);
	}
	else {
		throw std::runtime_error("realloc mem failed");
	}
}

//操作符求值
double calc(char op, double opNum) {
	double ret = 0;
	switch (op)
	{
	case '!':
		if (opNum > 0) {
			ret = 1;
			for (int i = 1; i <= opNum; i++) {
				ret *= i;
			}
		}
		break;
	default:
		throw std::runtime_error("not support single operator " + op);
		break;
	}

	return ret;
}

//操作符求值
double calc(double opNumFirst, char op, double opNumLast) {
	double ret = 0;
	switch (op)
	{
	case '+':
		ret = opNumFirst + opNumLast;
		break;
	case '-':
		ret = opNumFirst - opNumLast;
		break;
	case '*':
		ret = opNumFirst * opNumLast;
		break;
	case '/':
		ret = opNumFirst / opNumLast;
		break;
	case '^':
		ret = 1;
		for (int i = 0; i < opNumLast; i++) {
			ret *= opNumFirst;
		}
		break;
	default:
		exit(-3);
		break;
	}
	return ret;
}

//操作符转换
Operator optr2rank(char op) {
	switch (op)
	{
	case '+':
		return ADD;
	case '-':
		return SUB;
	case '*':
		return MUL;
	case '/':
		return DIV;
	case '^':
		return POW;
	case '!':
		return FAC;
	case '(':
		return L_P;
	case ')':
		return R_P;
	case '\0':
		return EOE;
	default:
		exit(-1);
	}
}

//比较栈顶运算符与运算符的优先级
char orderBetween(char opOnStack, char op) {
	return pri[optr2rank(opOnStack)][optr2rank(op)];
}

//表达式求值,并生成逆波兰表达式
double evaluate(char* S, char*& RPN) {
	Stack<char> opStack;
	Stack<double> opNumStack;
	opStack.push('\0');
	while (!opStack.empty()) {
		while (*S == ' ') {
			S++;
		}
		if (isdigit(*S)) {
			readNumber(S, opNumStack);
		}
		else {
			switch (orderBetween(opStack.top(), *S))
			{
			case '>':
				if ('!' == opStack.top()) {
					opNumStack.push(calc(opStack.pop(), opNumStack.pop()));
				}
				else {
					double opNumLast = opNumStack.pop();
					double opNumFirst = opNumStack.pop();
					opNumStack.push(calc(opNumFirst, opStack.pop(), opNumLast));
				}
				break;
			case '<':
				opStack.push(*S++);
				break;
			case '=':
				opStack.pop();
				S++;
				break;
			default:
				exit(-2);
			}
		}
	}
	return opNumStack.pop();
}