#include "Item.h"
#include "tree.h"
#include <string.h>
#include <stdlib.h>


void getinf(Info* from,Info* here) {
	here->inf_f = from->inf_f;
	if (from->inf_s != NULL) {
		here->inf_s = (char*)calloc(strlen(from->inf_s) + 1, sizeof(char));
		strcpy(here->inf_s, from->inf_s);
		free(from->inf_s);
	}
	else { here->inf_s = NULL; }
	//free(from);
}
void to_fl(char* str, double* re) {
	double help;
	*re = 0;
	int mn = 10, flag = 0;;
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] != '.') {
			if (flag == 0) {
				help = str[i] - '0';
				(*re) = (*re) * 10 + help;
			}
			else if (flag == 1) {
				help = str[i] - '0';
				*(re) += help / (mn);
				mn = mn * 10;
			}
		}
		else if (str[i] == '.') {
			flag = 1;
		}

	}
}
void to_int(char* str,int* re) {
	int help;
	*re = 0;
	for (int i = 0; i < strlen(str); i++) {
		help = str[i] - '0';
		(*re) = (*re) * 10 + help;
	}
}


