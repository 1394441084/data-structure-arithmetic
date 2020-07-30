#include "哈希表-链表.h"

void main(void) {
	//char* elems[] = { (char*)"翠花",(char*)"小芳",(char*)"苍老师" };//对变量进行强转
	char* elems[] = { "翠花","小芳","苍老师" };//属性 -> C/C++ ->语言 -> 符合模式项->否
	
	int i = 0;
	HashTable* HashTable;
	HashTable = InitHash(31);//初始化
	Insert(HashTable, 1, elems[0]);//插入数据
	Insert(HashTable, 2, elems[1]);
	Insert(HashTable, 3, elems[2]);
	Delete(HashTable, 1);
	for (i = 0; i < 4; i++) {
		Element e = Find(HashTable, i);
		if (e) {
			printf("%s\n", (const char*)Retrieve(e));
		}
		else {
			printf("Not found [key:%d]\n", i);
		}
	}
	system("pause");
}