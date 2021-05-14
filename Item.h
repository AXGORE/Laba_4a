#ifndef ITEM_H
#define ITEM_H
typedef struct Info Info;
typedef struct Info {
	double inf_f;
	char* inf_s;
	Info* next;
}Info;
void getinf(Info* from, Info* here);
void to_fl(char* str, double* re);
void to_int(char* str, int* re);








#endif // !1

