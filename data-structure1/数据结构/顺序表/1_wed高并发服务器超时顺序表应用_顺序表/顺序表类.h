#pragma once
#include <iostream>
#include <Windows.h>
using namespace std;

#define MAX_SIZE_1 100 //���ռ�

template <typename T = int>
struct ssqlist {
public:
	ssqlist() {
		elems = new T[MAX_SIZE_1];
		lenth = 0;
		head = 0;
		size = MAX_SIZE_1;
	}
	~ssqlist() {
		if (elems) {
			delete[] elems;//�ͷŴ洢�ռ�
			elems = NULL;
		}
		head = 0;
		lenth = 0;
		size = 0;
	}
	
	void printff() {
		cout << "˳�����ܿռ�:" << size << "\tԪ�ظ���:" << lenth << "\tԪ��ͷ��:"<<head<<endl;
		/*
		for (int i = head; i <= lenth - 1; i++) {
			cout << elems[i] << " ";
		}
		cout << endl;
		*/
	}

	bool Add_a_tail(T e) {//˳���β�����Ԫ��
		if (size == lenth + head) return false;	//�洢�ռ�����
		elems[lenth] = e;	//�ռ丳ֵ
		lenth++;	//����һ
		return true;
	}

	bool Insert(int i, T e) {//˳��������λ�ò���Ԫ��
		i--;
		if (i < 0 || i > lenth || lenth >= size)return false;//iֵ���Ϸ�

		//���ͷ��λ��!=0 && β��+ͷ��==size ��ôͷ�����пռ�,���Բ���Ԫ��
		if (head != 0 && lenth + head == size) {
			for (int j = head-1; j <= i; j++) {
				elems[j] = elems[j + 1];
			}
			elems[i] = e;
			lenth++;
			head++;
			return true;
		}
		
		for (int j = lenth; j >= i; j--) {
			elems[j] = elems[j - 1];//�����Ԫ�ؿ�ʼ����,ֱ���±�Ϊi��Ԫ�غ���
		}
		lenth++;
		elems[i] = e;
		return true;
	}

	bool deleteSqlist(int i) {//ɾ��ָ��λ�õ�Ԫ��
		if (i <= 0 || i > lenth)return false;//iֵ���Ϸ�
		i--;
		/*//β����ָ��λ��ɾ��Ԫ����ֿ�,��Ȼ������߼�����.�ֿ����ܸ��õ�ʹ��
		if (i == head) {//ɾ����һԪ��
			head++;
			lenth--;
			return true;
		}*/
		lenth--;
		if (i == lenth+ head) {//ɾ�����һ��Ԫ��
			return true;
		}
		for (int j = i; j < lenth + head; j++) {
			elems[j] = elems[j + 1];//ɾ��λ�õĺ���Ԫ��������ǰ��
		}
		return true;
	}

	void destruction() {//����˳���
		if (elems) {
			delete[] elems;//�ͷŴ洢�ռ�
			elems = NULL;
		}
		lenth = 0;
		size = 0;
	}
//private:
	int head;			//ͷ��
	T* elems = NULL;	//˳���Ļ���ַ
	int lenth = 0;		//˳���ĳ���(Ԫ�ظ���)
	int size = 0;		//˳����ܿռ��С
};


void The_order_sheet() {//˳���_main()
	ssqlist<int> list;

	list.printff();

	//���Ԫ��
	int count; int e;
	cout << "������Ҫ��ӵ�Ԫ�ظ���:";
	cin >> count;
	for (int i = 0; i < count; i++) {
		cout << "\n������Ҫ��ӵ�Ԫ��:";
		cin >> e;
		if (list.Add_a_tail(e)) {
			cout << "���Ԫ�سɹ�\n";
		}
		else {
			cout << "���Ԫ��ʧ��\n";
		}
	}
	list.printff();

	//����Ԫ��
	cout << "������Ҫ�����λ��:";
	cin >> count;
	cout << endl;
	cout << "������Ҫ���������Ԫ��:";
	cin >> e;
	if (list.Insert(count, e)) {
		cout << "����λ�ò���ɹ�\n";
		list.printff();
	}
	else {
		cout << "����λ�ò���ʧ��\n";
	}

	//ɾ��Ԫ��
	cout << "������Ҫɾ��Ԫ�ص�λ��:";
	cin >> count;
	if (list.deleteSqlist(count)) {
		cout << "ɾ���ɹ�\n";
		list.printff();
	}
	else {
		cout << "ɾ��ʧ��\n";
	}

	list.destruction();//���ٶ���
}
