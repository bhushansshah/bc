#include "postfix.h"
int convertToPostFix(char *sor, char *des){
	stack s;
	init(&s, 200);
	int num = 0;
	while(*sor != '\0'){
		if(*sor == ' '){
			if(*(des - 1) != ' ')
				*(des++) = ' ';
			sor++;
		}
		else if((*sor >= '0' && *sor <= '9') || *sor == '.'){
			if((*(sor - 1) < '0' || *(sor - 1) >'9') && *(sor - 1) != '.')
				num++;
			*(des++) = *(sor++);
		}
		else if(*sor == '('){
			if(*(des - 1) != ' '){
				*(des++) = ' ';
			}
			push(&s, *(sor++));
		}
		else if(*sor == ')'){
			if(*(des - 1) != ' '){
				*(des++) = ' ';
			}
			while(peek(s) != '('){
				*(des++) = pop(&s);
				*(des++) = ' ';
			}
			pop(&s);
			sor++;
		}
		else if(*sor == '/' || *sor == '*'){
			if(*(des - 1) != ' '){
				*(des++) = ' ';
			}
			while(!isEmpty(s) && (peek(s) == '*' || peek(s) == '/')){
				*(des++) = pop(&s);
				*(des++) = ' ';
			}
			push(&s, *(sor++));
		}
		else if(*sor == '-' || *sor == '+'){
			if(*(des - 1) != ' '){
				*(des++) = ' ';
			}
			while(!isEmpty(s) && (peek(s) == '/' || peek(s) == '*' || peek(s) == '+' || peek(s) == '-')){
				*(des++) = pop(&s);
				*(des++) = ' ';
			}
			push(&s, *(sor++));
		}
	}
	if(*(des - 1) != ' '){
		*(des++) = ' ';
	}
	while(!isEmpty(s)){
		*(des++) = pop(&s);
		*(des++) = ' ';
	}
	*(des) = '\0';
	return num;
}
