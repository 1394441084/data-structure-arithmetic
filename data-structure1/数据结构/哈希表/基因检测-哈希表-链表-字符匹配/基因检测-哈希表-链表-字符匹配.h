#pragma once
#define DEFAULT_SIZE 16 

/*��ϣ��Ԫ�ض���*/ 
typedef struct _ListNode { 
	struct _ListNode *next;
	void *key; void *data;
}ListNode;

typedef ListNode *List;
typedef ListNode *Element; 

/*��ϣ��ṹ����*/
typedef struct _HashTable { 
	int TableSize; List *Thelists; 
}HashTable;

/*��ϣ����*/ 
int Hash( void *key, int TableSize ); 

/*��ʼ����ϣ��*/ 
HashTable *InitHash( int TableSize );

 /*��ϣ�����*/ 
void Insert(HashTable * HashTable, void* key, void* value);

/*��ϣ�����*/ 
Element Find(HashTable* HashTable, void* key);

/*��ϣ������*/ 
void Destory(HashTable* HashTable); 

/*��ϣ��Ԫ������ȡ����*/ 
void* Retrieve(Element e);