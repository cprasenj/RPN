#include "rpn.h"

int isDigit(char ch){
	return ch >= '0' && ch <= '9';
}
int parseInt(char num) {
	return num - '0';
}
char getOperator(Stack stack){
	char sign = *(char *)pop(stack);
	return (sign<0) ? *(char *)pop(stack) : sign;
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
int perform(Stack operands,Stack operators) {
	int digit2 = *((int *)pop(operands)),digit1 = *((int *)pop(operands));
	operation(digit1,digit2,getOperator(operators),operands);
	return 1;
}
NUM digitCalculator(int index,char* expression) {
	NUM n;
	int exp = 0;
	for(;expression[index]!=32 || !expression[index+1];index++) 
		exp = exp*10 + parseInt(expression[index]);
	n.result = exp;
	n.index = index;
	return n;
}
int digitOperation(int i,char* expression,Stack operands) {
	NUM exp;
	int *tmp = (int *)malloc(sizeof(int*));
	exp = digitCalculator(i,expression);
	*tmp = exp.result;
	push(operands,tmp);
	return exp.index;
}
Result evaluate(char* expression){
	int i;
	Result res;
	Stack operators = createStack(),operands = createStack();
	for(i=0;expression[i];i++) 
		(isDigit(expression[i])) && (i = digitOperation(i,expression,operands)) ||
		(expression[i]!=32) && push(operators,&expression[i]) 
		&& operands.list->count>=2 && perform(operands,operators);
	operands.list->count>1 && (res.error = 0) || operators.list->count>1  
	&& (res.error = -1) && (res.result = 0) ||
	(res.error = 1) && (res.result = *((int *)(*(operands.top))->data));
	return res;
}