#include <stdlib.h>
typedef struct node{
	int val;
	struct node *next;
}node;

typedef struct number{
	node *head;
	int digits;
	int sign;
	int decimal;
}number;
number * inputNumber(char *s, int sign);
number * addNumbers(number *, number *);
number * subNumbers(number *, number *);
number * mulNumbers(number *, number *);
number * mulDigit(number *n1, int digit, int spaces);
number * divNumbers(number *, number *);
int greaterNumber(number *, number *);
void displayNumber(number *);
