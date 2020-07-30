#pragma once
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define DEFAULT_SIZE 16  //��ϣͰ // 24/6=4  //4����Ϊ��ϣͰ

typedef struct {
    void* *data;
    int key;
    int lenth = 0;		//˳���ĳ���(Ԫ�ظ���)
    int size = 0;		//˳����ܿռ��С
}sqlist;//����һ������

//��߿ɶ��ԺͿ�ά����
typedef sqlist* List;//˳���
typedef sqlist* Element;//Ԫ��

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

    hTable = (HashTable*)malloc(sizeof(HashTable));//��ϣ��

    if (NULL == hTable) {
        printf("HashTable malloc error.\n");
        return NULL;
    }

    hTable->TableSize = TableSize;

    //��ϣ���˳���ָ������
    //Ϊ Hash Ͱ�����ڴ�ռ䣬��Ϊһ��ָ������ //��ֵ�Ƶ�
    hTable->Thelists = new Element[TableSize]; //��ϣͰ��Ĵ�С // 24/6=4  //4����Ϊ��ϣͰ //0 1 2 3 

    if (NULL == hTable->Thelists) {
        printf("HashTable malloc error\n");
        free(hTable);
        return NULL;
    }

    //Ϊ Hash Ͱ��Ӧ��ָ�������ʼ������ڵ�
    for (i = 0; i < TableSize; i++) {

        //��ÿ����ϣͰ������ָ
        hTable->Thelists[i] = (sqlist*)malloc(sizeof(sqlist));//˳���ռ�

        if (NULL == hTable->Thelists[i]) {
            printf("HashTable malloc error\n");
            free(hTable->Thelists);
            free(hTable); 
            return NULL;
        }
        else {
            memset(hTable->Thelists[i], NULL , sizeof(sqlist));//������ڴ�����������ΪNULL
        }
    }
    return hTable;
}

/*�ӹ�ϣ���и��ݼ�ֵ����Ԫ��*/
Element Find(HashTable* HashTable, int key) {
    int i = 0;
    Element e = NULL;
    i = Hash(key, HashTable->TableSize);
    e = HashTable->Thelists[i];
    return e;
}

/*��ϣ�����Ԫ�أ�Ԫ��Ϊ��ֵ��*/ 
void Insert(HashTable* HashTable, int key, void* value) {
    Element e = NULL;
    e = Find(HashTable, key);
    if (NULL == e) {
        e = new sqlist;
        if (!e) {
            printf_s("91�г���\n");
            return;
        }
        //ͷ�巨
        e->data = new void*[DEFAULT_SIZE];
        if (!e->data) {
            printf_s("�ռ�û�з����!97��\n");
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
                printf_s("�ռ�û�з����!113��\n");
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
            printf_s("�˿ռ�����!125��\n");
            return;
        }
        e->data[e->lenth]=value;
        e->lenth++;
    }
}

/*��ϣ��ɾ��Ԫ�أ�Ԫ��Ϊ��ֵ��*/
void Delete(HashTable* HashTable, int key ,int key1) {//��ϣͰ //��ϣͰ��
    List L = NULL;
    int i = Hash(key, HashTable->TableSize); 
    L = HashTable->Thelists[i];
    if (!L || !L->data || L->size<key1) {
        printf_s("û�д洢����! 120��\n");
        return;
    }
    
    for (--key1; key1 >= L->lenth; key1++) {
        L->data[key1 - 1] = L->data[key1];
        L->data[key1] = NULL;
    }
    L->lenth--;
}

/*��ϣ��ɾ��Ԫ�أ�Ԫ��Ϊ��ֵ��*/
void Delete(HashTable* HashTable, int key) {//��ϣͰ
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

/*��ϣ��Ԫ������ȡ����*/ 
void* Retrieve(Element e) { //��ȡ���ǵ�������
    return e&&e->data ? e->data[0] : NULL;
}

/*���ٹ�ϣ��*/ 
void Destory(HashTable* H) { 
    for (int i = 0; i < H->TableSize; i++) { 
        if (H->Thelists[i]) {
            if (H->Thelists[i]->data) {
                delete[] H->Thelists[i]->data;//�������ݿ�
            }
            delete[] H->Thelists[i];//����˳���
        }
    }
    delete[] H->Thelists;//����˳���� //���ٹ�ϣ���˳������� //���ٹ�ϣͰ
    delete[] H;//���ٹ�ϣ��
}