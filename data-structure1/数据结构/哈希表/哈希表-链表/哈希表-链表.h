#pragma once
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define DEFAULT_SIZE 16  //��ϣͰ // 24/6=4  //4����Ϊ��ϣͰ

typedef struct _ListNode {//��
    struct _ListNode *next;//��һ���ڵ�
    int key; //��ֵ
    void *data; //����
}ListNode; 

//��߿ɶ��ԺͿ�ά����
typedef ListNode *List;//����
typedef ListNode *Element;//Ԫ��

typedef struct _HashTable { //��ϣ��
    int TableSize; //��ϣͰ������
    List *Thelists; //��ϣͰ��Ĵ�С // 24/6=4  //4����Ϊ��ϣͰ //0 1 2 3 
}HashTable;

//��ϣ���� 
/*���� key ������������λ Hash Ͱ��λ��*/ 
int Hash(int key, int TableSize) {
    return (key % TableSize);
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

    //Ϊ Hash Ͱ�����ڴ�ռ䣬��Ϊһ��ָ������ //��ֵ�Ƶ�
    hTable->Thelists = (List*)malloc(sizeof(List) * TableSize); //��ϣͰ��Ĵ�С // 24/6=4  //4����Ϊ��ϣͰ //0 1 2 3 

    if (NULL == hTable->Thelists) {
        printf("HashTable malloc error\n");
        free(hTable);
        return NULL;
    }

    //Ϊ Hash Ͱ��Ӧ��ָ�������ʼ������ڵ�
    for (i = 0; i < TableSize; i++) {

        //��ÿ����ϣͰ������ָ,ָ�������ͷ�ڵ�
        hTable->Thelists[i] = (ListNode*)malloc(sizeof(ListNode));

        if (NULL == hTable->Thelists[i]) {
            printf("HashTable malloc error\n");
            free(hTable->Thelists);
            free(hTable); return NULL;
        }
        else {
            memset(hTable->Thelists[i], 0, sizeof(ListNode));//������ڴ�����������Ϊ0 //����*next;key;data;
        }
    }
    return hTable;
}

/*�ӹ�ϣ���и��ݼ�ֵ����Ԫ��*/
Element Find(HashTable* HashTable, int key) {
    int i = 0;
    List L = NULL;
    Element e = NULL;
    i = Hash(key, HashTable->TableSize);
    L = HashTable->Thelists[i];//�ҵ�ͷ�ڵ�
    e = L->next;
    while (e != NULL && e->key != key) e = e->next;
    return e;
}

/*��ϣ�����Ԫ�أ�Ԫ��Ϊ��ֵ��*/ 
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

        L = HashTable->Thelists[Hash(key, HashTable->TableSize)];//ͷ�ڵ�
        //ǰ�巨
        tmp->data = value;
        tmp->key = key;
        tmp->next = L->next;
        L->next = tmp;
    }
    else {
        printf("the key already exist\n");//��key�Ѿ�����
    }
}

/*��ϣ��ɾ��Ԫ�أ�Ԫ��Ϊ��ֵ��*/
void Delete(HashTable* HashTable, int key) {
    Element e = NULL, last = NULL;
    List L = NULL;
    int i = Hash(key, HashTable->TableSize); 
    L = HashTable->Thelists[i];
    last = L;
    e = L->next;
    while (e != NULL && e->key != key) {
        last = e;//Ҫɾ������һ���ڵ�
        e = e->next;
    }
    if (e) {//�����ֵ�Դ��� 
        last->next = e->next;
        delete(e);
    }
}

/*��ϣ��Ԫ������ȡ����*/ 
void* Retrieve(Element e) { 
    return e ? e->data :
        NULL; 
}

/*���ٹ�ϣ��*/ 
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