#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include "numbers.h"
typedef struct numStack{
	number **A;
	int top;
	int size;
}numStack;
void initNs(numStack *s, int n);
int pushNs(numStack *, number *);
number * popNs(numStack *s);
//int peek(stack s);
bool isEmptyNs(numStack s);
bool isFullNs(numStack s);
