#include "Item.h"
#include "tree.h"
#include <string.h>
#include <stdlib.h>
#include "dialog.h"
#include <stdio.h>

int AddItem(Item* tree, Info* inf, int key, Item* next) {
	Item* start = tree;
	Item* next_help=NULL;
	Item* help1=NULL;
	Info* help;
	while (start->inf != NULL) {
		if (key > start->key) {
			if (start->right == NULL) {
				start->right = (Item*)calloc(1, sizeof(Item));
			}
			
			//AddItem(start, inf, key, next);
			//start = tree;
			next_help = start->right;
			help1 = start;
			
			start = start->right;
		}
		if (key < start->key) {
			if (start->left == NULL) {
				start->left = (Item*)calloc(1, sizeof(Item));
			}
			next = start;
			start = start->left;
			//AddItem(start, inf, key, next);
			//start = tree;
		}
		if (key == start->key && start->inf != NULL) {
			help = start->inf;
			while (help->next != NULL) {
				help = help->next;
			}
			help->next = (Info*)calloc(1, sizeof(Info));
			help = help->next;
			getinf(inf, help);
			break;
		}
	}
	if (start->inf == NULL) {
		start->inf = (Info*)calloc(1, sizeof(Info));
		getinf(inf, start->inf);
		start->key = key;
		//start->next = (Item*)calloc(1, sizeof(Item));
		start->next = next;
		//return 0;
	}
	if (help1 != NULL) {
		if (next_help->left == NULL) {
			help1->next = next_help;
		}
		else {
			while (next_help->left != NULL) {
				next_help = next_help->left;
			}
			help1->next = next_help;
		}
	}
}


int Del_Item(Item** tree, int key, int num) {
	Item* start = (*tree);
	if (start->inf == NULL) {
		Empty();
		return -1;
	}
	int n = 1;
	int flag=0;
	int a;
	int flag_l = 1;
	int flag_r = 1;
	Item* prev_h;
	prev_h = NULL;
	Item* help1;
	Info* help;
	Info* prev;
	prev = NULL;
	a=Find(&start,&prev_h, key);
	if (a == -1) {
		return -1; 
	}
	if (a == 1) { flag_l = 0; flag_r = 0; }
	if (start->key == key) {
		help = start->inf;
		while (help!=NULL && n != num) {
			flag = 1;
			prev = help;
			help = help->next;
			n++;
		}
		if (help == NULL) { return -1; }
		if (help->next != NULL) { flag = 1; }
		 if (n == num) {
			if (flag == 1 && prev != NULL) {
				prev->next = help->next;
			}
			else if (flag == 1 && prev == NULL) {
				start->inf = help->next;
			}
		    free(help->inf_s);
			free(help);
		 }
		if (flag == 0) {
			if (flag_l == 0 && flag_r == 0) {
				if (start->left != NULL && start->right != NULL) {
					Cp_Item(start->next, start);
					help1 = (*tree);
					if (start->right == start->next) { prev_h = start; }
					else {
						prev_h = start->right;
						while (prev_h->left != start->next) { prev_h = prev_h->left; }
					}
					Del(start->next, prev_h, help1);
					return 0;
				}
				else if (start->left == NULL && start->right == NULL) {
					free(start);
					(*tree) = (Item*)calloc(1, sizeof(Item));
					return 0;
				}
				else if (start->left == NULL && start->right != NULL) {
					(*tree) = start->right;
					free(start);
					return 0;
				}
				else if (start->left != NULL && start->right == NULL) {
					(*tree) = start->left;
					prev_h = (*tree);
					while (prev_h->right != NULL) { prev_h = prev_h->right; }
					prev_h->next = NULL;
					free(start);
					return 0;
				}
			}
			if (start->left != NULL && start->right != NULL) {
				Cp_Item(start->next, start);
				help1 = (*tree);
				if (start->right == start->next) { prev_h = start; }
				else {
					prev_h = start->right;
					while (prev_h->left != start->next) { prev_h = prev_h->left; }
				}
				Del(start->next, prev_h,help1);
				return 0;
			}
			else {
				help1 = (*tree);
				int m=Del(start, prev_h, help1);
				if (m == 1) {
					Cp_Item(start->next, start);
					if (start->right == start->next) { prev_h = start; }
					else {
						prev_h = start->right;
						while (prev_h->left != start->next) { prev_h = prev_h->left; }
					}
					Del(start->next, prev_h, help1);
					return 0;
				
				}
				return 0;
			}
		}
	}
}

void Cp_Item(Item* from, Item* here) {
	here->inf = from->inf;
	here->key = from->key;
}



int Del(Item* start, Item* prev_h, Item* tree){

	Item* par = start;
	int a=Find_par(tree, &par);
	if (a == 0) {
		if (prev_h == start->next) {
			free(start);
			prev_h->left = NULL;
			return 0;
		}
		else {
			return 1;
		}
	}
	par->next = start->next;
	if (start->left == NULL && start->right == NULL) {
		if (prev_h->right == start) {
			prev_h->right = NULL;
		}
		if (prev_h->left == start) {
			prev_h->left = NULL;
		}
		free(start);
		return 0;
	}
	if (start->left == NULL) {
		if (prev_h->right == start) {
			prev_h->right = start->right;
		}
		if (prev_h->left == start) {
			prev_h->left = start->right;
		}
		free(start);
		return 0;
	}
	if (start->left != NULL) {
		if (prev_h->right == start) {
			prev_h->right = start->left;
		}
		if (prev_h->left == start) {
			prev_h->left = start->left;
		}
		free(start);
		return 0;
	}
}
int Find_par(Item* tree, Item** start) {
	while (tree->left != NULL) { 
		tree = tree->left;
	}
	if (tree == (*start)) { return 0; }
	while (tree->next != (*start)) { 
		tree = tree->next;
	}
	*start = tree;
	return 1;
}




int Find(Item** start, Item** prev, int key) {
	int n;
	int flag_l = 0;
	int flag_r = 0;
	if ((*start)->inf == NULL) {
		Empty();
		return -1;
	}
	if (key == (*start)->key) {
		if (flag_r == 1) {
			return 0;
		}
		else if (flag_l == 1) {
			return 0;
		}
		else { return 1; }
	}
	while ((*start)->key != key) {
		flag_l = 0;
		flag_r = 0;
		while (key < (*start)->key && (*start) != NULL) {
			(*prev) = (*start);
			(*start) = (*start)->left;
			flag_l = 1;
			if ((*start) == NULL) {
				return -1;
			}
		}
		while (key > (*start)->key && (*start) != NULL) {
			(*prev) = (*start);
			(*start) = (*start)->right;
			flag_r = 1;
			if ((*start) == NULL) {
				return -1;
			}
		}
		if ((*start) == NULL) {
			return -1;
		}
	}
	if (key == (*start)->key) {
		if (flag_r == 1) {
			return 0;
		}
		else if (flag_l == 1) {
			return 0;
		}
		else { return 1; }
	}
}
 
 void Show_in_range(Item* tree, int from, int to) {
	Item* start = tree;
	if (start->inf == NULL) {
		Empty();
		return;
	}
	int flag = 0;
	while (start->left != NULL) {
		start = start->left;
	}
	while (from > start->key && start!= NULL) {
		start = start->next;
		if (start == NULL) {
			No_Elements();
			return;
		}
	}
	while (to >= start->key && start!=NULL) {
		flag = 1;
		show_inf(start);
		start = start->next;
		if (start == NULL) {
			return;
		}
	}
	if (flag == 0) {
		No_Elements();
	}
}

 void Find_min(Item* tree) {
	 Item* start = tree;
	 if (start->inf == NULL) {
		 Empty();
		 return;
	 }
	 while (start->left != NULL) {
		 start = start->left;
	 }
	 show_inf(start);
 }

 void free_tree(Item* tree) {
	 Item* help;
	 Info* help_1;
	 Info* help2;
	 Item* start = tree;
	 if (start->inf == NULL) {
		 free(tree);
		 return;
	 }
	 while (tree->left != NULL) {
		 tree = tree->left;
     }
	 while (tree != NULL) {
		 help = tree;
		 tree = tree->next;
		 help_1 = help->inf;
		 while (help_1->next != NULL) {
			 help2 = help_1;
			 free(help2->inf_s);
			 help_1 = help_1->next;
			 free(help2);
		 }
		 free(help_1->inf_s);
		 free(help_1);
		 free(help);
	 }
	 free(tree);
 }

int load(Item* tree, char* name) {
	 FILE* f = NULL;
	 char** inf;
	 char** inf_help;
	 Item* next = NULL;
	 char* prov;
	 int key;
	 int flag;
	 double inf2;
	 f = fopen(name, "r+b");
	 if (f == NULL) {
		 return -1;
	 }
	 Info* help = (Info*)calloc(1, sizeof(Info));
	 inf = (char**)calloc(3, sizeof(char*));
	 for (int i = 0; i < 3; i++) {
		 inf[i] = (char*)calloc(255, sizeof(char));
	 }
	 flag = 1;
	 inf_help = (char**)calloc(3, sizeof(char*));
	 while (flag == 1) {
		 for (int i = 0; i < 3; i++) {
			 inf_help[i] = (char*)calloc(255, sizeof(char));
		 }
		 for (int i = 0; i < 3; i++) {
			 prov = fgets(inf[i], 255, f);
			 if (prov == NULL) {
				 flag = 0;
				 break;
			 }
			 strncpy(inf_help[i], inf[i], strlen(inf[i]) - 2);

		 }
		 if (flag == 0) {
			 for (int i = 0; i < 3; i++) {
				 free(inf_help[i]);
			 }
			 break; }
		 to_int(inf_help[0], &key);
		 to_fl(inf_help[1], &inf2);
		 help->inf_f = inf2;
		 help->inf_s = inf_help[2];
		 AddItem(tree,help,key,next);
		 for (int i = 0; i < 2; i++) {
			 free(inf_help[i]);
		 }
	 }
	 for (int i = 0; i < 3; i++) {
		 free(inf[i]);
	 }
	 free(inf);
	 free(inf_help);
	 free(help);
	 fclose(f);
	 return 0;
 }
 void print_tree(Item* tree, int i) {
	 if (tree == NULL) { return; }
	 print_tree(tree->right, i + 1);
	 for (int j = 0; j < i; j++) {
		 printf("\t");
	 }
	 printf("%d\n", tree->key);
	 print_tree(tree->left, i + 1);
 }