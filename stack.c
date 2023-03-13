#include "stack.h"
#include <stdlib.h>
#include <limits.h>
void init(stack *s, int n){
	s->A = malloc(sizeof(int) * n);
	s->size = n;
	s->top = -1;
}
int push(stack *s, int value){
	if(s->top >= s->size - 1)
		return 1;
	s->A[++(s->top)] = value;
}
int pop(stack *s){
	if(s->top <= -1)
		return INT_MIN;
	return s->A[(s->top)--];
}
int peek(stack s){
	if(s.top <= -1)
		return INT_MIN;
	return s.A[s.top];
}
bool isEmpty(stack s){
	return s.top <= -1;
}
bool isFull(stack s){
	return s.top >= (s.size - 1);
}
