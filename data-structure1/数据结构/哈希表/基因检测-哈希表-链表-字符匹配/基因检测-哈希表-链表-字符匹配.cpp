#include "������-��ϣ��-����-�ַ�ƥ��.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 

#define BUCKET_SIZE 1024 
//strncpy((const char*)a + 1, (const char*)b, 4);//123456+ƫ��,223456,�Ƚ�ǰ��λ:2345,2345
#define compare(a,b) strcmp((const char*)a, (const char*)b) //���ַ����Ƿ���� 
#define hash_func SDBMHash //�������ֵ�keyӳ��Ϊ���� //�ٶ�SDBM ��ϣ

unsigned int SDBMHash(void *key) { //�������ֵ�keyӳ��Ϊ���� 
	unsigned int hash = 0;
	char *str = (char*)key;
	while (*str) { 
		// equivalent to: hash = 65599*hash + (*str++);
		hash = (*str++) + (hash << 6) + (hash << 16) - hash; 
		//ͨ��λ�Ʊ���ӳ�䵽ͬһ��key //ADBCCD�е�DD��CC����
		//��ǰ���о�����λ��6��16�ص�������С��
	}
	return (hash & 0x7FFFFFFF); 
}

/*���� key ������������λ Hash Ͱ��λ��*/
int Hash(void *key, int TableSize) { 
	//return (key%TableSize);
	 return hash_func(key) % TableSize; //"CDBC" => 16011 %1024 =>
	 //return 0; 
}

/*��ʼ����ϣ��*/ 
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
	//Ϊ Hash Ͱ�����ڴ�ռ䣬��Ϊһ��ָ������ 
	hTable->Thelists = (List*)malloc(sizeof(List) * TableSize);
	if (NULL == hTable->Thelists) {
		printf("HashTable malloc error\n");
		free(hTable);
		return NULL;
	}
	//Ϊ Hash Ͱ��Ӧ��ָ�������ʼ������ڵ� 
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

/*�ӹ�ϣ���и��ݼ�ֵ����Ԫ��*/ 
Element Find(HashTable* HashTable, void* key) {
	int i = 0;
	List L = NULL;
	Element e = NULL;
	i = Hash(key, HashTable->TableSize);
	L = HashTable->Thelists[i];
	e = L->next;
	while (e != NULL && compare(e->key, key) != 0) {//�ַ����Ƚ�
		e = e->next;
	}
	return e;
}

/*��ϣ�����Ԫ�أ�Ԫ��Ϊ��ֵ��*/ 
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
		L = HashTable->Thelists[code];//ǰ�巨
		tmp->data = value;
		tmp->key = key;
		tmp->next = L->next; L->next = tmp;
	}
	else
		printf("the key already exist\n");
}
		
/*��ϣ��ɾ��Ԫ�أ�Ԫ��Ϊ��ֵ��*/ 
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
	if (e) {//�����ֵ�Դ��� 
		last->next = e->next;
		free(e);
	}
}

/*��ϣ��Ԫ������ȡ����*/ 
void *Retrieve(Element e) { 
	return e?e->data:NULL; 
}

/*���ٹ�ϣ��*/ 
void Destory(HashTable* HashTable) {
	int i = 0;
	List L = NULL;
	Element cur = NULL, next = NULL;
	for (i = 0; i < HashTable->TableSize; i++) {
		L = HashTable->Thelists[i];
		cur = L->next;
		while (cur != NULL) {//�ͷ�����ڵ�
			next = cur->next;
			free(cur);
			cur = next;
		}
		free(L);
	}
	free(HashTable->Thelists);//�ͷŹ�ϣͰ
	free(HashTable);//�ͷŹ�ϣ��
}

void main(void) {
	char* elems[] = { "ADBB","BDDC","CDBC","BDBB" };
	char* tester = "ABDBBBAC"; 
	char cur[5] = { '\0' };//�洢Ҫ������
	int i = 0;
	HashTable* HashTable = NULL;
	HashTable = InitHash(BUCKET_SIZE);
	Insert(HashTable, elems[0], elems[0]);
	Insert(HashTable, elems[1], elems[1]);
	Insert(HashTable, elems[2], elems[2]);
	Insert(HashTable, elems[3], elems[3]);
	//Delete(HashTable, elems[0]);

	strncpy_s(cur, tester+1, 4);//BDBB'\0' //����
	Element e = Find(HashTable, cur);
	if (e) {
		printf("%s\n", (const char*)Retrieve(e));
	}
	else {
		printf("Not found [key:%s]\n", cur);
	}
	system("pause");
}