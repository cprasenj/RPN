#include <stdio.h>
#include "rpn.h"

struct num{
	int result;
	int index;
};

typedef struct num NUM;
int isDigit(char ch){
	return ch >= '0' && ch <= '9';
}

int parseInt(char num) {
	return num - '0';
}

char getOperator(Stack stack){
	char sign = *(char *)pop(stack);
	return (sign==32) ? *(char *)pop(stack) : sign;
}

void operation(int o1,int o2,char op,Stack operands) {
	int res,*tmp;
	op == '+' && (res = o1+o2);
	op == '-' && (res = o1-o2);
	op == '*' && (res = o1*o2);
	op == '/' && (res = o1/o2);
	tmp = malloc(sizeof(int));
	*tmp = res;
	push(operands,tmp);
}

void Do(Stack operands,Stack operators) {
	int digit2,digit1;
	char ot;
	digit2 = *((char *)pop(operands));
	digit1 = *((char *)pop(operands));
		ot = *(char *)pop(operators);
	operation(digit1,digit2,ot,operands);
}

NUM digitCalculator(int index,char* expression) {
	NUM n;
	int exp = 0;
	for(;expression[index+1]==32;index++)
		exp = exp*10 + parseInt(expression[index]);
	n.result = exp;
	n.index = index;
	return n;
}

int evaluate(char* expression){
	int i,result,o1,o2,op,*tmp,j,reference;
	NUM exp;
	Stack operators = createStack(),operands = createStack();
	for(i=0;expression[i];i++) {
		tmp = (int *)malloc(sizeof(int*));
		if(isDigit(expression[i])){
			exp = digitCalculator(i,expression);
			*tmp = exp.result;
			i = exp.index;
			push(operands,tmp);
		}
		else
			(expression[i]!=' ') && push(operators,&expression[i]);
	}
	for(;operands.list->count>=2;){
		Do(operands,operators);
	}
	return *((int *)(*(operands.top))->data);
}



