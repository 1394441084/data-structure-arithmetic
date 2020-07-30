#include "基因检测-哈希表-链表-字符匹配.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 

#define BUCKET_SIZE 1024 
//strncpy((const char*)a + 1, (const char*)b, 4);//123456+偏移,223456,比较前四位:2345,2345
#define compare(a,b) strcmp((const char*)a, (const char*)b) //两字符串是否相等 
#define hash_func SDBMHash //不是数字的key映射为数字 //百度SDBM 哈希

unsigned int SDBMHash(void *key) { //不是数字的key映射为数字 
	unsigned int hash = 0;
	char *str = (char*)key;
	while (*str) { 
		// equivalent to: hash = 65599*hash + (*str++);
		hash = (*str++) + (hash << 6) + (hash << 16) - hash; 
		//通过位移避免映射到同一个key //ADBCCD中的DD和CC这样
		//经前人研究发现位移6和16重叠性是最小的
	}
	return (hash & 0x7FFFFFFF); 
}

/*根据 key 计算索引，定位 Hash 桶的位置*/
int Hash(void *key, int TableSize) { 
	//return (key%TableSize);
	 return hash_func(key) % TableSize; //"CDBC" => 16011 %1024 =>
	 //return 0; 
}

/*初始化哈希表*/ 
HashTable* InitHash(int TableSize) {
	int i = 0;
	HashTable* hTable = NULL;
	if (TableSize <= 0) {
		TableSize = DEFAULT_SIZE;
	}
	hTable = (HashTable*)malloc(sizeof(HashTable));
	if (NULL == hTable) {
		printf("HashTable malloc error.\n");
		return NULL;
	}
	hTable->TableSize = TableSize;
	//为 Hash 桶分配内存空间，其为一个指针数组 
	hTable->Thelists = (List*)malloc(sizeof(List) * TableSize);
	if (NULL == hTable->Thelists) {
		printf("HashTable malloc error\n");
		free(hTable);
		return NULL;
	}
	//为 Hash 桶对应的指针数组初始化链表节点 
	for (i = 0; i < TableSize; i++) {
		hTable->Thelists[i] = (ListNode*)malloc(sizeof(ListNode));
		if (NULL == hTable->Thelists[i]) {
			printf("HashTable malloc error\n");
			free(hTable->Thelists);
			free(hTable);
			return NULL;
		}
		else {
			memset(hTable->Thelists[i], 0, sizeof(ListNode));
		}
	}
	return hTable;
}

/*从哈希表中根据键值查找元素*/ 
Element Find(HashTable* HashTable, void* key) {
	int i = 0;
	List L = NULL;
	Element e = NULL;
	i = Hash(key, HashTable->TableSize);
	L = HashTable->Thelists[i];
	e = L->next;
	while (e != NULL && compare(e->key, key) != 0) {//字符串比较
		e = e->next;
	}
	return e;
}

/*哈希表插入元素，元素为键值对*/ 
void Insert(HashTable* HashTable, void* key, void* value) {
	Element e = NULL, tmp = NULL;
	List L = NULL;
	e = Find(HashTable, key);
	if (NULL == e) {
		tmp = (Element)malloc(sizeof(ListNode));
		if (NULL == tmp) {
			printf("malloc error\n");
			return;
		}
		int code = Hash(key, HashTable->TableSize);
		L = HashTable->Thelists[code];//前插法
		tmp->data = value;
		tmp->key = key;
		tmp->next = L->next; L->next = tmp;
	}
	else
		printf("the key already exist\n");
}
		
/*哈希表删除元素，元素为键值对*/ 
void Delete(HashTable* HashTable, void* key) {
	Element e = NULL, last = NULL;
	List L = NULL;
	int i = Hash(key, HashTable->TableSize);
	L = HashTable->Thelists[i];
	last = L;
	e = L->next;
	while (e != NULL && e->key != key) {
		last = e;
		e = e->next;
	}
	if (e) {//如果键值对存在 
		last->next = e->next;
		free(e);
	}
}

/*哈希表元素中提取数据*/ 
void *Retrieve(Element e) { 
	return e?e->data:NULL; 
}

/*销毁哈希表*/ 
void Destory(HashTable* HashTable) {
	int i = 0;
	List L = NULL;
	Element cur = NULL, next = NULL;
	for (i = 0; i < HashTable->TableSize; i++) {
		L = HashTable->Thelists[i];
		cur = L->next;
		while (cur != NULL) {//释放链表节点
			next = cur->next;
			free(cur);
			cur = next;
		}
		free(L);
	}
	free(HashTable->Thelists);//释放哈希桶
	free(HashTable);//释放哈希表
}

void main(void) {
	char* elems[] = { "ADBB","BDDC","CDBC","BDBB" };
	char* tester = "ABDBBBAC"; 
	char cur[5] = { '\0' };//存储要检测的数
	int i = 0;
	HashTable* HashTable = NULL;
	HashTable = InitHash(BUCKET_SIZE);
	Insert(HashTable, elems[0], elems[0]);
	Insert(HashTable, elems[1], elems[1]);
	Insert(HashTable, elems[2], elems[2]);
	Insert(HashTable, elems[3], elems[3]);
	//Delete(HashTable, elems[0]);

	strncpy_s(cur, tester+1, 4);//BDBB'\0' //拷贝
	Element e = Find(HashTable, cur);
	if (e) {
		printf("%s\n", (const char*)Retrieve(e));
	}
	else {
		printf("Not found [key:%s]\n", cur);
	}
	system("pause");
}