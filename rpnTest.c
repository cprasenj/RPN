#include "rpn.h"
#include "expr_assert.h"
#include <stdio.h>
#include <stdlib.h>

#define log(test_description) int log = printf("**  Description->%s\n\n", test_description)

void test_evaluate_001(){
	log("evaluate works for +");
	assertEqual(evaluate("1 2 3 4 5 + + + +"),15);
}

void test_evaluate_002(){
	log("evaluate works for *");
	assertEqual(evaluate("1 2 3 4 5 * * * *"),120);
}

void test_evaluate_003(){
	log("evaluate works for /");
	assertEqual(evaluate("6 2 /"),3);
}

void test_evaluate_004(){
	log("evaluate works for -");
	assertEqual(evaluate("6 2 -"),4);
}

// void test_evaluate_005(){
// 	log("evaluate works for complex equation");
// 	assertEqual(evaluate("5 + ((1 + 2) * 4) − 3"),7);
// }
