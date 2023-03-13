#include "numStack.h"
void initNs(numStack *s, int n){
	s->A = malloc(sizeof(number *) * n);
	s->size = n;
	s->top = -1;
}
int pushNs(numStack *s, number *num){
	if(s->top >= s->size - 1)
		return 1;
	s->A[++(s->top)] = num;
	return 0;
}
number * popNs(numStack *s){
	if(s->top <= -1)
		return NULL;
	return s->A[(s->top)--];
}
/*int peek(stack s){
	if(s.top <= -1)
		return INT_MIN;
	return s.A[s.top];
}*/
bool isEmptyNs(numStack s){
	return s.top <= -1;
}
bool isFullNs(numStack s){
	return s.top >= (s.size - 1);
}
