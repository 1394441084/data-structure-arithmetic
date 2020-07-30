#pragma once

#include <iostream>
#include <Windows.h>
using namespace std;

#define MAX_SIZE_2 6 //���ռ�

/*
typedef struct _sqlist sqlist;
struct _sqlist {
	int* elems;  //˳���Ļ���ַ
	int lenth;   //˳���ĳ���(Ԫ�ظ���)
	int size;    //˳����ܿռ��С
};*/

typedef struct {
	int* elems=NULL;		//˳���Ļ���ַ
	int lenth=0;		//˳���ĳ���(Ԫ�ظ���)
	int size=0;		//˳����ܿռ��С
}sqlist;//����һ������
//}sqlist,sqlist1;//����������

bool initsqlist(sqlist &other) {//����һ���յ�˳���
	other.elems = new int[MAX_SIZE_2];//Ϊ˳������ MAX_SIZE ���ռ�
	if (!other.elems)return false;//������� //�洢ʧ��
	other.lenth = 0;
	other.size = MAX_SIZE_2;
	return true;
}

void sqlistprintf(const sqlist &list) {//�������˳���
	cout << "˳�����ܿռ�:" << list.size << "\t˳����Ԫ�ظ���:" << list.lenth << endl;
	for (int i = 0; i <= list.lenth-1; i++) {
		cout << list.elems[i] << " ";
	}
	cout << endl;
}

bool listAdd_a_tail(sqlist& list,int e) {//˳���β�����Ԫ��
	if (list.size == list.lenth) return false;	//�洢�ռ�����

	list.elems[list.lenth] = e;	//�ռ丳ֵ
	list.lenth++;	//����һ
	return true;
}

bool listInsert(sqlist& list,int i,int e) {//˳��������λ�ò���Ԫ��
	i--;
	if (i < 0 || i > list.lenth || list.lenth >=list.size)return false;//iֵ���Ϸ� 
	for (int j = list.lenth; j >= i ; j--) {
		list.elems[j] = list.elems[j-1];//�����Ԫ�ؿ�ʼ����,ֱ���±�Ϊi��Ԫ�غ���
	}
	list.lenth++;
	list.elems[i] = e;
	return true;
}

bool listdelete(sqlist& list, int i) {//ɾ��ָ��λ�õ�Ԫ��
	if (i <= 0 || i > list.lenth )return false;//iֵ���Ϸ�
	i--;
	list.lenth--;
	if (i == list.lenth) {//ɾ�����һ��Ԫ��
		return true;
	}
	for (int j = i; j < list.lenth; j++) {
		list.elems[j] = list.elems[j+1];//ɾ��λ�õĺ���Ԫ��������ǰ��
	}
	return true;
}

void listdestruction(sqlist& list) {//����˳���
	if (list.elems) {
		delete[] list.elems;//�ͷŴ洢�ռ�
		list.elems = NULL;
	}
	list.lenth = 0;
	list.size = 0;
}

void The_order_sheet_main() {//˳���_main()
	sqlist list;
	cout << "˳����ʼ����-------\n";
	if (initsqlist(list)) {
		cout << "˳����ʼ���ɹ�\n";
		sqlistprintf(list);
	}
	else {
		cout << "˳����ʼ��ʧ��\n";
	}

	//���Ԫ��
	int count; int e;
	cout << "������Ҫ��ӵ�Ԫ�ظ���:";
	cin >> count;
	for (int i = 0; i < count; i++) {
		cout << "\n������Ҫ��ӵ�Ԫ��:";
		cin >> e;
		if (listAdd_a_tail(list, e)) {
			cout << "���Ԫ�سɹ�\n";
		}
		else {
			cout << "���Ԫ��ʧ��\n";
		}
	}
	sqlistprintf(list);

	//����Ԫ��
	cout << "������Ҫ�����λ��:";
	cin >> count;
	cout << endl;
	cout << "������Ҫ���������Ԫ��:";
	cin >> e;
	if (listInsert(list, count, e)) {
		cout << "����λ�ò���ɹ�\n";
		sqlistprintf(list);
	}
	else {
		cout << "����λ�ò���ʧ��\n";
	}

	//ɾ��Ԫ��
	cout << "������Ҫɾ��Ԫ�ص�λ��:";
	cin >> count;
	if (listdelete(list, count)) {
		cout << "ɾ���ɹ�\n";
		sqlistprintf(list);
	}
	else {
		cout << "ɾ��ʧ��\n";
	}

	listdestruction(list);
}

