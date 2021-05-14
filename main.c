#include "Item.h"
#include "tree.h"
#include <string.h>
#include <stdlib.h>
#include "dialog.h"
#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

int main() {
	Info* inf = (Info*)calloc(1, sizeof(Info));
	Item* tree = (Item*)calloc(1, sizeof(Item));
	Item* next=NULL;
	int release,key;
	char* name;
	int a,f1=0,f2=0,n;
	int vsp;
	//_crtBreakAlloc = 77;
	do {
		printf("Use file?\n1. Yes\n2. No\n");
		Get_int(&n);
	if (n > 2) { printf("%s\n", "Error, try again "); }
	if (n == 1) {
		printf("\nEnter File name-->\n");
		while (getchar() != '\n');
		name = Get_str();
		if (name == NULL) { break; }
		a=load(tree,name); 
		if (a == -1) {
			No_File();
		}
		else {
			free(name);
			break;
		}
		free(name);
	}
	if (n == 2) { break; }
	} while (1==1);
	do {
		Item* start = tree;
		a = dialog(&key, &inf,&release);
		if (a == 1) {
			AddItem(tree,inf,key,next);
		}
		if (a == 2) {
			vsp=Del_Item(&tree,key,release);
			if (vsp == -1) { No_Key(); }
		}
		if (a == 3) {
			vsp = Find(&start,&start,key);
			if (vsp == -1) { No_Key(); }
			else { show_inf(start); }
		}
		if (a == 4) {
			Show_in_range(tree, key, release);
		}
		if (a == 5) {
			Find_min(tree);
		}
		if (a == 6) {
			show_tree(tree);
			print_tree(start, 0);
		}
		if (a == 8) {
			D_Timing();
		}
	} while (a != 7);
	free_tree(tree);
	free(inf);
	_CrtDumpMemoryLeaks();
	return 0;
}
