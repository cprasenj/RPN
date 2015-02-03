#include "rpn.h"
#include "expr_assert.h"
#include <stdio.h>
#include <stdlib.h>

#define log(test_description) int log = printf("**  Description->%s\n\n", test_description)

void test_evaluate_001(){
	log("evaluate works for +");
	assertEqual(evaluate("1 2 3 4 5 + + + +").result,15);
}

void test_evaluate_002(){
	log("evaluate works for *");
	assertEqual(evaluate("1 2 3 4 5 * * * *").result,120);
}

void test_evaluate_003(){
	log("evaluate works for /");
	assertEqual(evaluate("6 2 /").result,3);
}

void test_evaluate_004(){
	log("evaluate works for -");
	assertEqual(evaluate("6 2 -").result,4);
}

void test_evaluate_006(){
	log("evaluate works for complex equation");
	assertEqual(evaluate("5 1 2 + 4 * + 3 -").result,14);
}

void test_evaluate_007(){
	log("evaluate works for complex equation");
	assertEqual(evaluate("2 2 2 * 2 - 3 + + ").result,7);
	assertEqual(evaluate("2 2 2 2 2 * * 2 + + 2 - *").result,20);
	assertEqual(evaluate("2 2 2 2 2 * * 2 + + 2 - *").error,1);
}

void test_evaluate_008(){
	log("evaluate works for -");
	assertEqual(evaluate("61 21 -").result,40);
}

void test_evaluate_009(){
	log("evaluate works for -");
	assertEqual(evaluate("6666 2222 +").result,8888);
}
