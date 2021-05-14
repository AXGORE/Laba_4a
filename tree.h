#ifndef TREE_H
#define TREE_H
typedef struct Info Info;
typedef struct Item Item;
typedef struct Item {
	int key;
	Info* inf;
	Item* right;
	Item* left;
	Item* next;
}Item;
int AddItem(Item* tree, Info* inf, int key, Item* next);
int Find(Item** start, Item** prev, int key);
int Del_Item(Item** tree, int key, int num);
void Show_in_range(Item* tree, int from, int to);
void Find_min(Item* tree);
void Cp_Item(Item* from, Item* here);
void free_tree(Item* tree);
int load(Item* tree, char* name);
void print_tree(Item* tree, int i);


#endif // !TREE_H

