#pragma once
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define DEFAULT_SIZE 16  //哈希桶 // 24/6=4  //4组是为哈希桶

typedef struct {
    void* *data;
    int key;
    int lenth = 0;		//顺序表的长度(元素个数)
    int size = 0;		//顺序表总空间大小
}sqlist;//定义一个别名

//提高可读性和可维护性
typedef sqlist* List;//顺序表
typedef sqlist* Element;//元素

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

    hTable = (HashTable*)malloc(sizeof(HashTable));//哈希表

    if (NULL == hTable) {
        printf("HashTable malloc error.\n");
        return NULL;
    }

    hTable->TableSize = TableSize;

    //哈希表的顺序表指针数组
    //为 Hash 桶分配内存空间，其为一个指针数组 //键值似的
    hTable->Thelists = new Element[TableSize]; //哈希桶表的大小 // 24/6=4  //4组是为哈希桶 //0 1 2 3 

    if (NULL == hTable->Thelists) {
        printf("HashTable malloc error\n");
        free(hTable);
        return NULL;
    }

    //为 Hash 桶对应的指针数组初始化链表节点
    for (i = 0; i < TableSize; i++) {

        //让每个哈希桶都有所指
        hTable->Thelists[i] = (sqlist*)malloc(sizeof(sqlist));//顺序表空间

        if (NULL == hTable->Thelists[i]) {
            printf("HashTable malloc error\n");
            free(hTable->Thelists);
            free(hTable); 
            return NULL;
        }
        else {
            memset(hTable->Thelists[i], NULL , sizeof(sqlist));//分配的内存所有数据置为NULL
        }
    }
    return hTable;
}

/*从哈希表中根据键值查找元素*/
Element Find(HashTable* HashTable, int key) {
    int i = 0;
    Element e = NULL;
    i = Hash(key, HashTable->TableSize);
    e = HashTable->Thelists[i];
    return e;
}

/*哈希表插入元素，元素为键值对*/ 
void Insert(HashTable* HashTable, int key, void* value) {
    Element e = NULL;
    e = Find(HashTable, key);
    if (NULL == e) {
        e = new sqlist;
        if (!e) {
            printf_s("91行出错\n");
            return;
        }
        //头插法
        e->data = new void*[DEFAULT_SIZE];
        if (!e->data) {
            printf_s("空间没有分配好!97行\n");
            return;
        }
        for (int i = 0; i < DEFAULT_SIZE; i++) {e->data[i] = NULL; }
        e->data[0] = value;
        e->key = key;
        e->size = DEFAULT_SIZE;
        e->lenth = 1;
        HashTable->Thelists[Hash(key, HashTable->TableSize)] = e;
    }else {
        if (!e->data) {
            e->data = new void* [DEFAULT_SIZE];
            if (!e->data) {
                printf_s("空间没有分配好!113行\n");
                return;
            }

            for (int i = 0; i < DEFAULT_SIZE; i++) { e->data[i] = NULL; }

            e->data[0] = value;
            e->key = key;
            e->size = DEFAULT_SIZE;
            e->lenth = 1;
            return;
        }
        
        if (e->lenth >= DEFAULT_SIZE) {
            printf_s("此空间已满!125行\n");
            return;
        }
        e->data[e->lenth]=value;
        e->lenth++;
    }
}

/*哈希表删除元素，元素为键值对*/
void Delete(HashTable* HashTable, int key ,int key1) {//哈希桶 //哈希桶里
    List L = NULL;
    int i = Hash(key, HashTable->TableSize); 
    L = HashTable->Thelists[i];
    if (!L || !L->data || L->size<key1) {
        printf_s("没有存储数据! 120行\n");
        return;
    }
    
    for (--key1; key1 >= L->lenth; key1++) {
        L->data[key1 - 1] = L->data[key1];
        L->data[key1] = NULL;
    }
    L->lenth--;
}

/*哈希表删除元素，元素为键值对*/
void Delete(HashTable* HashTable, int key) {//哈希桶
    List L = NULL;
    int i = Hash(key, HashTable->TableSize);
    L = HashTable->Thelists[i];
    if (!L || !L->data) {
        return;
    }
    delete[] L->data;
    delete L;
    HashTable->Thelists[i] = NULL;
}

/*哈希表元素中提取数据*/ 
void* Retrieve(Element e) { //提取的是单个数据
    return e&&e->data ? e->data[0] : NULL;
}

/*销毁哈希表*/ 
void Destory(HashTable* H) { 
    for (int i = 0; i < H->TableSize; i++) { 
        if (H->Thelists[i]) {
            if (H->Thelists[i]->data) {
                delete[] H->Thelists[i]->data;//销毁数据库
            }
            delete[] H->Thelists[i];//销毁顺序表
        }
    }
    delete[] H->Thelists;//销毁顺序表库 //销毁哈希表的顺序表数组 //销毁哈希桶
    delete[] H;//销毁哈希表
}