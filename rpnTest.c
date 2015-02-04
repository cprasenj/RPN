#include "rpn.h"
#include "expr_assert.h"
#include <stdio.h>
#include <stdlib.h>

// #define log(test_description) int log = printf("**  Description->%s\n\n", test_description)
#define everything void
typedef void (*logger)(char*);

struct con{
	logger log;
};

void log(char* desc){
	printf("%s\n",desc);
}

struct con console = {&log};



void cout(char * d){
	console.log(d);
}
struct system{
	struct{
		void(*println)(char*);
	} out;
};

struct system System = {{cout}};


everything test_evaluate_001(){
	System.out.println("evaluate works for +");
	assertEqual(evaluate("1 2 3 4 5 + + + +").result,15);
}

void test_evaluate_002(){
	console.log("evaluate works for *");
	assertEqual(evaluate("1 2 3 4 5 * * * *").result,120);
}

void test_evaluate_003(){
	cout("evaluate works for /");
	assertEqual(evaluate("6 2 /").result,3);
}

void test_evaluate_004(){
	System.out.println("evaluate works for -");
	assertEqual(evaluate("6 2 -").result,4);
}

void test_evaluate_006(){
	console.log("evaluate works for complex equation");
	assertEqual(evaluate("5 1 2 + 4 * + 3 -").result,14);
}

void test_evaluate_007(){
	cout("evaluate works for complex equation");
	assertEqual(evaluate("2 2 2 * 2 - 3 + + ").result,7);
	assertEqual(evaluate("2 2 2 2 2 * * 2 + + 2 - *").result,20);
	assertEqual(evaluate("2 2 2 2 2 * * 2 + + 2 - *").error,1);
}

void test_evaluate_008(){
	System.out.println("evaluate works for -");
	assertEqual(evaluate("61 21 -").result,40);
}

void test_evaluate_009(){
	console.log("evaluate works for -");
	assertEqual(evaluate("6666 2222 +").result,8888);
}

void test_isOperator_001() {
	cout("Gives 1 if given char is an operator");
	assertEqual(isOperator('*'),1);
}

void test_isOperator_002() {
	System.out.println("Gives 0 if given char is an operator");
	assertEqual(isOperator('Q'),0);
}
everything test_precedence_001() {
	console.log("gives 0 for + or -");
	assertEqual(precedence('+'),0);
	assertEqual(precedence('-'),0);
	assertEqual(precedence('*'),1);
	assertEqual(precedence('/'),1);
	assertEqual(precedence('^'),2);
}