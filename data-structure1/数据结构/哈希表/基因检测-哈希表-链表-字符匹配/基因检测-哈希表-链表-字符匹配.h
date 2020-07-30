#pragma once
#define DEFAULT_SIZE 16 

/*哈希表元素定义*/ 
typedef struct _ListNode { 
	struct _ListNode *next;
	void *key; void *data;
}ListNode;

typedef ListNode *List;
typedef ListNode *Element; 

/*哈希表结构定义*/
typedef struct _HashTable { 
	int TableSize; List *Thelists; 
}HashTable;

/*哈希函数*/ 
int Hash( void *key, int TableSize ); 

/*初始化哈希表*/ 
HashTable *InitHash( int TableSize );

 /*哈希表插入*/ 
void Insert(HashTable * HashTable, void* key, void* value);

/*哈希表查找*/ 
Element Find(HashTable* HashTable, void* key);

/*哈希表销毁*/ 
void Destory(HashTable* HashTable); 

/*哈希表元素中提取数据*/ 
void* Retrieve(Element e);