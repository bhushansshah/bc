#include "numStack.h"
#include "stack.h"
#include <stdio.h>
number * inputNumber(char *s, int sign){
	node *h = NULL;
	node *n;
	int d = 0;
	int decimal = 0, flag = 0;
	number *result = malloc(sizeof(number));
	while((*s >= '0' && *s <= '9') || *s == '.'){
		n = malloc(sizeof(node));
		n->val = *s - '0';
		n->next = h;
		h = n;
		d++;
		if(flag)
			decimal++;
		if(*s == '.'){
			flag = 1;
			d--;
		}
		s++;
	}
	result->head = h;
	result->digits = d;
	result->sign = sign;
	result->decimal = decimal;
	return result;
}

number * addNumbers(number *n1, number *n2){
	number *result = malloc(sizeof(number));
	node *num1 = n1->head;
	node *num2 = n2->head;
	if(n1->sign == n2->sign){
		result->sign = n1->sign;
	}
	else if(n1->sign){
		n2->sign = 1;
		return subNumbers(n1, n2);
	}
	else{
		n1->sign = 1;
		return subNumbers(n2, n1);
	}
	node *end = NULL;
	node *n;
	int s = 0, c = 0;
	int d = 0;
	if((n1->decimal || n2->decimal) &&(n1->decimal != n2->decimal)){
		if(n1->decimal > n2->decimal){
			result->decimal = n1->decimal;
			for(int i = 0; i < n1->decimal - n2->decimal; i++){
				n = malloc(sizeof(node));
				n->val = num1->val;
				n->next = NULL;
				d++;
				if(!end){
					result->head = n;
					end = n;
				}
				else{
					end->next = n;
					end = n;
				}
				num1 = num1->next;
			}
			if(num1->val == -2){
				n = malloc(sizeof(node));
				n->val = -2;
				n->next = NULL;
				end->next = n;
				end = n;
				num1 = num1->next;
			}

		}
		else{
			result->decimal = n2->decimal;
			for(int i = 0; i < n2->decimal - n1->decimal; i++){
				n = malloc(sizeof(node));
				n->val = num2->val;
				n->next = NULL;
				d++;
				if(!end){
					result->head = n;
					end = n;
				}
				else{
					end->next = n;
					end = n;
				}
				num2 = num2->next;
			}
			if(num2->val == -2){
				n = malloc(sizeof(node));
				n->val = -2;
				n->next = NULL;
				end->next = n;
				end = n;
				num2 = num2->next;
			}
		}
	}

	while(num1 && num2){
		if(num1->val == -2){
			n = malloc(sizeof(node));
			n->val = -2;
			n->next = NULL;
			end->next = n;
			end = n;
		}
		else{
			d++;
			s = (num1->val + num2->val + c) % 10;
			c = (num1->val + num2->val + c) / 10;
			n = malloc(sizeof(node));
			n->val = s;
			n->next = NULL;
			if(!end){
				result->head = n;
				end = n;
			}
			else{
				end->next = n;
				end = n;
			}
		}
		num1 = num1->next;
		num2 = num2->next;
	}
	while(num1){
		d++;
		s = (num1->val + c) % 10;
		c = (num1->val + c) / 10;
		n = malloc(sizeof(node));
		n->val = s;
		n->next = NULL;
		if(!end){
			result->head = n;
			end = n;
		}
		else{
			end->next = n;
			end = n;
		}
		num1 = num1->next;
	}
	while(num2){
		d++;
		s = (num2->val + c) % 10;
		c = (num2->val + c) / 10;
		n = malloc(sizeof(node));
		n->val = s;
		n->next = NULL;
		if(!end){
			result->head = n;
			end = n;
		}
		else{
			end->next = n;
			end = n;
		}
		num2 = num2->next;
	}
	if(c){
		d++;
		n = malloc(sizeof(node));
		n->val = c;
		n->next = NULL;
		end->next = n;
		end = n;
	}
	result->digits = d;
	return result;
}

number * subNumbers(number *n1, number *n2){
	/*displayNumber(n1);
	printf("\n");
	displayNumber(n2);
	printf("\n");
	printf("%d	%d\n", n1->sign, n2->sign);*/
	if(n1->sign == 1 && n2->sign == 0){
		n2->sign = 1;
		return addNumbers(n1, n2);
	}
	else if(n1->sign == 0 && n2->sign == 1){
		n2->sign  = 0;
		return addNumbers(n1, n2);
	}
	node *num1 = n1->head;
	node *num2 = n2->head;
	node *n, *end = NULL;
	node *greater, *smaller;
	number *result = malloc(sizeof(number));
	node *temp;
	if(n1->decimal > n2->decimal){
		n2->digits += n1->decimal - n2->decimal;
		if(!n2->decimal){
			n = malloc(sizeof(node));
			n->val = -2;
			n->next = num2;
			num2 = n;
		}
		for(int i = 0; i < n1->decimal - n2->decimal; i++){
			n = malloc(sizeof(node));
			n->val = 0;
			n->next = num2;
			num2 = n;
		}
		n2->decimal = n1->decimal;
		n2->head = num2;
	}
	else{
		n1->digits += n2->decimal - n1->decimal;
		if(n2->decimal && !n1->decimal){
			n = malloc(sizeof(node));
			n->val = -2;
			n->next = num1;
			num1 = n;
		}
		for(int i = 0; i < n2->decimal - n1->decimal; i++){
			n = malloc(sizeof(node));
			n->val = 0;
			n->next = num1;
			num1 = n;
		}
		n1->decimal = n2->decimal;
		n1->head = num1;
	}
	if(greaterNumber(n1, n2)){
		greater = num1;
		smaller = num2;
		result->sign = n1->sign;
		result->decimal = n1->decimal;
		result->digits = n1->digits;
	}
	else{
		greater = num2;
		smaller = num1;
		result->sign = !n1->sign;
		result->decimal = n1->decimal;
		result->digits = n2->digits;
	}
	while(greater && smaller){
		if(greater->val == -2){
			n = malloc(sizeof(node));
			n->val = -2;
			n->next = NULL;
			end->next = n;
			end = n;
		}
		else if(greater->val >= smaller->val){
			n = malloc(sizeof(node));
			n->val = greater->val - smaller->val;
			n->next = NULL;
			if(!end){
				end = n;
				result->head = n;
			}
			else{
				end->next = n;
				end = n;
			}
		}
		else{
			greater->val += 10;
			n = malloc(sizeof(node));
			n->val = greater->val - smaller->val;
			n->next = NULL;
			if(!end){
				end = n;
				result->head = n;
			}
			else{
				end->next = n;
				end = n;
			}
			temp = greater->next;
			while(temp->val <= 0){
				if(temp->val != -2)
					temp->val = 9;
				temp = temp->next;
			}
			temp->val--;
		}
		greater = greater->next;
		smaller = smaller->next;
	}
	while(greater){
		n = malloc(sizeof(node));
		n->val = greater->val;
		n->next = NULL;
		end->next = n;
		end = n;
		greater = greater->next;
	}
	
	return result;
}
number * mulNumbers(number *n1, number *n2){
	numStack ns;
	initNs(&ns, n2->digits + 2);
	node *num2 = n2->head, *n;
	number *p1, *p2, *result;
	int zeros = 0;
	/*displayNumber(n1);
	printf("\n");
	displayNumber(n2);
	printf("\n");
	return NULL;*/
	/*while(num2){
		printf("%d ", num2->val);
		num2 = num2->next;
	}
	printf("Finish\n");
	return NULL;*/
	while(num2){
		if(num2->val != -2){
			pushNs(&ns, mulDigit(n1, num2->val, zeros));
			zeros++;
		}
		num2 = num2->next;
	}
	/*while(!isEmptyNs(ns)){
		displayNumber(popNs(&ns));
		printf("\n");
	}
	printf("%d\n", zeros);
	printf("%d\n", n2->digits);
	return NULL;*/
	while(ns.top + 1 > 1){
		p1 = popNs(&ns);
		p2 = popNs(&ns);
		pushNs(&ns, addNumbers(p1, p2));
	}
	
	result = popNs(&ns);
	result->sign = (n1->sign == n2->sign);
	result->decimal = n1->decimal + n2->decimal;
	if(result->decimal){
		num2 = result->head;
		for(int i = 0; i < result->decimal - 1; i++){
			num2 = num2->next;
		}
		n = malloc(sizeof(node));
		n->val = -2;
		n->next = num2->next;
		num2->next = n;
	}
	return result;
}
number * mulDigit(number *n1, int digit, int spaces){
	number *result = malloc(sizeof(number));
	result->sign = 1;
	result->decimal = 0;
	node *end = NULL, *n;
	node *num1 = n1->head;
	int s = 0, c = 0, d = 0;
	/*displayNumber(n1);
	printf("\n	%d\n", digit);
	return NULL;*/
	for(int i = 0; i < spaces; i++){
		n = malloc(sizeof(node));
		n->val = 0;
		n->next = NULL;
		d++;
		if(!end){
			end = n;
			result->head = n;
		}
		else{
			end->next = n;
			end = n;
		}
	}
	while(num1){
		if(num1->val != -2){
			s = (num1->val * digit + c) % 10;
			c = (num1->val * digit + c) / 10;
			n = malloc(sizeof(node));
			n->val = s;
			n->next = NULL;
			d++;
			if(!end){
				end = n;
				result->head = n;
			}
			else{
				end->next = n;
				end = n;
			}
		}
		num1 = num1->next;
	}
	if(c){
		n = malloc(sizeof(node));
		n->val = c;
		n->next = NULL;
		end->next = n;
		end = n;
		d++;
	}
	result->digits = d;
	return result;
}
number * divNumbers(number *n1, number *n2){
	return NULL;
}
void displayNumber(number *num){
	if(!num){
		return;
	}
	if(!num->head){
		if(num->sign == 0){
			printf("-");
		}
		return;
	}
	int v = num->head->val;
	num->head = num->head->next;
	displayNumber(num);
	if(v == -2){
		printf(".");
	}
	else{
		printf("%d", v);
	}
}

int greaterNumber(number *n1, number *n2){
	if(n1->sign == 1 && n2->sign == 0)
		return 1;
	if(n1->sign == 0 && n2->sign == 1)
		return 0;
	if(n1->digits - n1->decimal > n2->digits - n2->decimal){
		return 1;
	}
	else if(n1->digits - n1->decimal < n2->digits - n2->decimal){
		return 0;
	}
	node *num1 = n1->head;
	node *num2 = n2->head;
	stack s1, s2;
	int val1, val2;
	init(&s1, n1->digits + 2);
	init(&s2, n2->digits + 2);
	while(num1){
		push(&s1, num1->val);
		num1 = num1->next;
	}
	while(num2){
		push(&s2, num2->val);
		num2 = num2->next;
	}
	while(!isEmpty(s1) && !isEmpty(s2)){
		val1 = pop(&s1);
		val2 = pop(&s2);
		if(val1 > val2){
			return 1;
		}
		else if(val2 > val1){
			return 0;
		}
	}
	return !isEmpty(s1);
	

}
