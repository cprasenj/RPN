#include "rpn.h"
#include "expr_assert.h"
#include <stdio.h>
#include <stdlib.h>

#define log(test_description) int log = printf("**  Description->%s\n\n", test_description)

void test_evaluate(){
	assertEqual(evaluate("1 2 3 4 5 + + + +"),15);
}