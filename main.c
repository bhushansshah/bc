#include <stdio.h>
#include <string.h>
#include "postfix.h"
#include "numStack.h"
int main(int size, char *agrs[]){
	char des[200];
	char sor[200];
	int len = 0;
	int ind = 1, desind = 0;
	int stackSize;
	char *exp;
	char *iter;
	number *n1, *n2;
	sor[0] = ' ';
	for(int i = 1; i < size; i++){
		exp = agrs[i];
		while(*exp != '\0'){
			sor[ind++] = *exp;
			exp++;
		}
		sor[ind++] = ' ';
	}
	sor[ind] = '\0';
	printf("%s\n", sor);
	ind = 1;
	if(sor[1] == '-'){
		des[0] = '-';
		desind++;
		ind = 2;
		while(sor[ind] < '0' || sor[ind] > '9'){
			ind++;
		}
	}
	else if(sor[1] == '+'){
		ind = 2;
		while(sor[ind] < '0' || sor[ind] > '9'){
			ind++;
		}
	}
	stackSize = convertToPostFix(sor + ind, des +  desind);
	printf("%s\n", des);
	numStack ns;
	initNs(&ns, stackSize);
	iter = des;
	while(*iter != '\0'){
		if(desind){
			iter++;
			pushNs(&ns, inputNumber(iter, 0));
			while((*iter >= '0' && *iter <= '9') || *iter == '.'){
				iter++;
			}
			desind = 0;
		}
		if(*iter >= '0' && *iter <= '9'){
			pushNs(&ns, inputNumber(iter, 1));
			while((*iter >= '0' && *iter <= '9') || *iter == '.'){
				iter++;
			}
		}
		if(*iter != ' '){
			n2 = popNs(&ns);
			n1 = popNs(&ns);
			switch(*iter){
				case '+' :
					pushNs(&ns, addNumbers(n1,n2));
					break;
				case '-' :
					pushNs(&ns, subNumbers(n1, n2));
					break;
				case '*' :
					pushNs(&ns, mulNumbers(n1, n2));
					break;
				case '/' : 
					pushNs(&ns, divNumbers(n1, n2));
					break;
			}
		}
		iter++;
	}
	displayNumber(popNs(&ns));
	printf("\n");
	return 0;
}
