#include "rpn.h"
#include <string.h>
int isDigit(char ch){
	return (ch >= '0' && ch <= '9') ? 1 : 0;
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
	for(;expression[index]!=32 || !expression[index];index++) 
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
//====================================================================================
int isOperator(char ch) {
	char a[] = {'+','-','*','/','^'};
	int i;
	for(i=0;i<4;i++)
		if(a[i] == ch) return 1;
	return 0;
}

int precedence(char sign) {
	int precedence = -1;
	(sign == '+' || sign == '-') && (precedence = 0);
	(sign == '/' || sign == '*') && (precedence = 1);
	sign == '^' && (precedence = 2);
	return precedence;
}

int firstLevelOperation(Stack operands,Stack operators, int index,char* expression) {
	expression[index+2] == '(' &&
	(index = parenthesisOperation(operands,operators,index+2,expression)) ||
	push(operands,&expression[index+2]);
	push(operands,&expression[index]);
	return index+2;
}

int secondLevelOneOperation(Stack operands,Stack operators,int index,char* expression) {
	int i,count = 0,j;
	push(operators,&expression[index]);
	expression[index+2] == '(' && 
	(parenthesisOperation(operands,operators,index+2,expression)) || 
	push(operands,&expression[index+2]);
	return index+2;
}

int parenthesisOperation(Stack operands,Stack operators,int index,char* expression) {
	int i;
	for(i = index;expression[i+2]!=')';i+=2){
	expression[i+1] == '(' && parenthesisOperation(operands,operators,i+1,expression);	
	isDigit(expression[i+2]) && (i = digitOperation(index+2,expression,operands));
	if(precedence(expression[i+1])>=0)
		i = rankWiseOperation(precedence(expression[i+1]),operands,operators,index,expression)+3;
	}
	return index++;
}

int rankWiseOperation(int rank,Stack operands,Stack operators,int index,char* expression) {
	!rank && push(operators,&expression[index]) && index++;
	(rank == 1) && (index = firstLevelOperation(operands,operators,index,expression));
	(rank == 2) && (index = secondLevelOneOperation(operands,operators,index,expression));
	return index;
}

int infixOperation(Stack operands,Stack operators,int index,char* expression){
	int rank;
	isDigit(expression[index]) && (index = infixDigitOperation(index,expression,operands));
	rank = precedence(expression[index]);
	if(rank>=0)
		index = rankWiseOperation(rank,operands,operators,index,expression);
	expression[index] == '(' && (index = parenthesisOperation(operands,operators,index,expression));
	return index;
}

int infixDigitOperation(int i,char* expression,Stack operands) {
	NUM exp;
	char *tmp = (int *)malloc(sizeof(char*));
	exp = digitCalculator(i,expression);
	*tmp = exp.result+'0';
	push(operands,tmp);
	return exp.index;
}

void reverse(char* array,int length) {
	int i;
	char tmp;
	for(i = 0;i<length/2;i++){
		tmp = array[i];
		array[i] = array[length-i-1];
		array[length-i-1] = tmp;
	}
}

char* infixToPostfix(char* expression) {
	int i;
	Stack operators = createStack(),operands = createStack();
	char *result = (char*)malloc(sizeof(char)*strlen(expression)); 
	for(i=0;expression[i];i++)
		i = infixOperation(operands,operators,i,expression);
	for(i=0;*operands.top;i++)
		(result[i] = *(char*)pop(operands)) && result[i] == '(' && i--;
	reverse(result,i);
	for(;*operators.top;i++)
		(result[i] = *(char*)pop(operators)) && result[i] == '(' && i--;	
	return result;
}










	




















