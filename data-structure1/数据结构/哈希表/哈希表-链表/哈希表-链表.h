#pragma once
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define DEFAULT_SIZE 16  //哈希桶 // 24/6=4  //4组是为哈希桶

typedef struct _ListNode {//链
    struct _ListNode *next;//下一个节点
    int key; //键值
    void *data; //数据
}ListNode; 

//提高可读性和可维护性
typedef ListNode *List;//链表
typedef ListNode *Element;//元素

typedef struct _HashTable { //哈希表
    int TableSize; //哈希桶的数量
    List *Thelists; //哈希桶表的大小 // 24/6=4  //4组是为哈希桶 //0 1 2 3 
}HashTable;

//哈希函数 
/*根据 key 计算索引，定位 Hash 桶的位置*/ 
int Hash(int key, int TableSize) {
    return (key % TableSize);
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

    //为 Hash 桶分配内存空间，其为一个指针数组 //键值似的
    hTable->Thelists = (List*)malloc(sizeof(List) * TableSize); //哈希桶表的大小 // 24/6=4  //4组是为哈希桶 //0 1 2 3 

    if (NULL == hTable->Thelists) {
        printf("HashTable malloc error\n");
        free(hTable);
        return NULL;
    }

    //为 Hash 桶对应的指针数组初始化链表节点
    for (i = 0; i < TableSize; i++) {

        //让每个哈希桶都有所指,指向链表的头节点
        hTable->Thelists[i] = (ListNode*)malloc(sizeof(ListNode));

        if (NULL == hTable->Thelists[i]) {
            printf("HashTable malloc error\n");
            free(hTable->Thelists);
            free(hTable); return NULL;
        }
        else {
            memset(hTable->Thelists[i], 0, sizeof(ListNode));//分配的内存所有数据置为0 //包括*next;key;data;
        }
    }
    return hTable;
}

/*从哈希表中根据键值查找元素*/
Element Find(HashTable* HashTable, int key) {
    int i = 0;
    List L = NULL;
    Element e = NULL;
    i = Hash(key, HashTable->TableSize);
    L = HashTable->Thelists[i];//找到头节点
    e = L->next;
    while (e != NULL && e->key != key) e = e->next;
    return e;
}

/*哈希表插入元素，元素为键值对*/ 
void Insert(HashTable* HashTable, int key, void* value) {
    Element e = NULL, tmp = NULL;
    List L = NULL;
    e = Find(HashTable, key);
    if (NULL == e) {
        tmp = (Element)malloc(sizeof(ListNode));
        if (NULL == tmp) {
            printf("malloc error\n");
            return;
        }

        L = HashTable->Thelists[Hash(key, HashTable->TableSize)];//头节点
        //前插法
        tmp->data = value;
        tmp->key = key;
        tmp->next = L->next;
        L->next = tmp;
    }
    else {
        printf("the key already exist\n");//此key已经存在
    }
}

/*哈希表删除元素，元素为键值对*/
void Delete(HashTable* HashTable, int key) {
    Element e = NULL, last = NULL;
    List L = NULL;
    int i = Hash(key, HashTable->TableSize); 
    L = HashTable->Thelists[i];
    last = L;
    e = L->next;
    while (e != NULL && e->key != key) {
        last = e;//要删除的上一个节点
        e = e->next;
    }
    if (e) {//如果键值对存在 
        last->next = e->next;
        delete(e);
    }
}

/*哈希表元素中提取数据*/ 
void* Retrieve(Element e) { 
    return e ? e->data :
        NULL; 
}

/*销毁哈希表*/ 
void Destory(HashTable* HashTable) { 
    int i = 0; 
    List L = NULL; 
    Element cur = NULL, next = NULL;
    for (i = 0; i < HashTable->TableSize; i++) { 
        L = HashTable->Thelists[i]; 
        cur = L->next; 
        while (cur != NULL) { 
            next = cur->next; 
            free(cur);
            cur = next; 
        }
        free(L);
    }
    free(HashTable->Thelists);
    free(HashTable); 
}