#include <stdbool.h>
typedef struct stack{
	int *A;
	int top;
	int size;
}stack;
void init(stack *s, int n);
int push(stack *s, int value);
int pop(stack *s);
int peek(stack s);
bool isEmpty(stack s);
bool isFull(stack s);
