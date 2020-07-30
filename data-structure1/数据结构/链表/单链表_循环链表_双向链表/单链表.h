#pragma once
#include <iostream>
using namespace std;

//�������:��ٶ��������֪����ɶ��,���Ǹ�������
typedef struct _structNode {//����ʵ�ֲ���
	 int data=NULL;//�ڵ�����
	_structNode* next=NULL;//��һ������ڵ�
}linklist, structNode;//�����׽ڵ�,����ڵ�;//������������Ч����

//������ĳ�ʼ��(linklistָ�����͵�����)
bool Initlist(linklist*  &L) {//ֻ��ʼ��ͷ�ڵ�
	L = new structNode;//����һ���ڵ�

	if (!L)return false;//���ɽڵ�ʧ��
	L->data=NULL;
	L->next = NULL;//���ڵ���ΪNULL
	return true;//��ʼ���ɹ�
}

//ǰ�巨 (�׽ڵ�,����Ľڵ�)
bool inser_front(linklist* &L, structNode* &node) {
	if (!L || !node)return false;//�ж��Ƿ�Ϊ��
	/*
	
	if (L->next == NULL) {
		L->data = node->data;
		node->data = NULL;
		node->next = NULL;
		L->next = node;
	}
	else {
		L->data = node->data;
		node->data = L->data;
		node->next = L->next;//ԭ�׽ڵ����һ���ڵ��ַ,�ɽ�����,�µ���һ���ڵ�ӹ�
		L->next = node;//�׽ڵ����һ���ڵ��ַ�滻���½ڵ��ַ
	}*/

	//L->data = node->data;//0=1:1 1=2:L=2 2=3:L=3
	//node->data = L->data;//1=0:0 2=1:n=1 3=2:n=2
	node->next = L->next;//ԭ�׽ڵ����һ���ڵ��ַ,�ɽ�����,�µ���һ���ڵ�ӹ�
	L->next = node;//�׽ڵ����һ���ڵ��ַ�滻���½ڵ��ַ

		return true;
}

//��巨()
bool inser_back(linklist* &L, structNode* &node) {
	if (!L || !node)return false;//�ж��Ƿ�Ϊ��
	structNode *last=L;//β��
	while (last->next) { 
		last =last->next;
	}//������ָ��β���ڵ���
	
	node->next = NULL;//��β�ڵ�->next��ΪNULL
	last->next = node;//β�ڵ�->nextָ���½ڵ�,�½ڵ��Ϊ��β�ڵ�
	return true;
}

//��ָ��λ�ú����
bool inser(linklist*& L,int i,int &e) {
	if (!L || i <= 0 )return false;//�ж��Ƿ�Ϊ��
	i--;//����ǲ�����λ����
	structNode* last = L;
	int j = 0;
	while (last->next && j<i) {
		j++;
		last = last->next;
	}//������ָ���ǽڵ���
	if (!last->next && j < i)return false;//��������λ����

	structNode* last1 = new structNode;//�½ڵ�
	last1->data = e;
	last1->next = last->next;
	last->next = last1;

	return true;
}

//������ȡֵ
bool linked_list_value(linklist*& L, int i, int& e) {
	if (!L || !L->next || i<=0)return false;//�ж��Ƿ�Ϊ��
	structNode* last = L->next;
	int j = 1;

	while (last->next && j < i) {
		j++;
		last = last->next;
	}//������ָ���ǽڵ���

	if (!last->next && j < i)return false;//��������λ����

	e = last->data;

	return true;
}

//���������Ԫ��
bool linked_list_search_data(linklist*& L, int data,int & i) {//��ֵ����
	if (!L || !L->next) {i = -1;return false;}//�ж��Ƿ�Ϊ��
	structNode* last = L->next;
	i = 1;
	while (last) {
		if (last->data == data)return true;//���ݶ�����,����
		i++;
		last = last->next;
	}//������ָ���ǽڵ���

	i = -1;
	return false;
}

//������ɾ��Ԫ������
bool linked_list_delete_data(linklist*& L, int data) {
	if (!L || !L->next) {return false; }//�ж��Ƿ�Ϊ��
	structNode* last = L;
	
	while (last->next) {
		if (last->next->data == data) {//1
			structNode* last1;
			last1 = last->next;//1
			last->next = last1->next;//1=3
			delete last1;
			return true;//���ݶ�����,����
		}
		last = last->next;
	}//������ָ���ǽڵ���

	return false;
}

//������λ��ɾ��Ԫ��
bool linked_list_delete_site(linklist*& L, int i) {
	if (!L || !L->next ||i<=0) { return false; }//�ж��Ƿ�Ϊ��
	structNode* last = L;
	
	int j = 1;

	while (last->next && i>j) {
		last = last->next;
		j++;
	}//������ָ���ǽڵ���

	if (!last->next || j < i)return false;

	structNode* last1;
	last1 = last->next;//1
	last->next = last1->next;//1=3
	delete last1;
	return true;//���ݶ�����,����
}

//���ٵ�����
void linked_list_delete(linklist*& L) {
	structNode* last = L;
	while (last) {
		L = L->next;//ָ����һ���ڵ�
		//cout << "ɾ��Ԫ��:" << last->data << endl;
		delete last;//ɾ��ͷ�ڵ�
		last = L;
	}
}

//���������
void single_linked_list_output(linklist* &L) {
	if (!L) {
		cout << "������Ϊ��\n";
		return;
	}
	structNode* p = L->next;
	
	while (p) {
		cout << p->data << "\t";
		p = p->next;
	}
	cout << endl;
}


void single_linked_list_main() {
	linklist* L = NULL;//�����׽ڵ�
	Initlist(L);//��ʼ��һ���յ�����
	
	//ʹ��ǰ�巨��������
	int n=0; structNode* s = NULL; int x = 0;

	cout << "ǰ�巨����������\n";
	cout << "������Ԫ�ظ���:";
	cin >> n;
	cout << "\n����������" << n << "��Ԫ��:\n";

	while (n > 0) {
		s = new structNode;//�����½ڵ�
		cin >> s->data;
		inser_front(L, s);
		--n;
	}

	//����������
	single_linked_list_output(L);
	
	//ʹ�ú�巨��������
	//int n; structNode* s = NULL;
	cout << "��巨����������\n";
	cout << "������Ԫ�ظ���:";
	cin >> n;
	cout << "\n����������" << n << "��Ԫ��:\n";

	while (n > 0) {
		s = new structNode;//�����½ڵ�
		cin >> s->data;
		inser_back(L, s);//�����Ľ�����
		n--;
	}
	
	//����������
	single_linked_list_output(L);

	//������λ�ò���Ԫ��
	for(int i=0;i<-3;i++){
		cout << "���������λ�ú�Ԫ��(�ÿո����):\n";
		cin >> n >> x;
		
		if (inser(L,n,x)) {single_linked_list_output(L);}
		else {cout << "����ʧ��!\n";}
	}
	
	//��ָ��λ��ȡ������ֵ
	for (int i = 0; i < -6; i++) {
		cout << "������ȡֵλ��:\n";
		cin >> n;
		if (linked_list_value(L, n, x)) {
			cout << "����ĵ�" << n << "��Ԫ��:" << x << endl;
		}
		else {
			cout << "ȡָʧ��!\n";
		}
	}

	//��Ԫ��(�洢������)����ѯ�ڵ������Ƿ�洢,�������ĸ�λ��
	//cout << "����������ҵ�Ԫ��:\n";
	//while(cin>>n){
		while (0) {
		if (linked_list_search_data(L, n, x)) {
			cout << "Ԫ��: " << n << " ������ĵ�" << x <<"λ��."<< endl;
		}
		else {
			cout << "û�д�Ԫ��\n";
		}
		cout << "����������ҵ�Ԫ��:\n";
	}
	
	//��ָ��λ��ɾ��Ԫ�� 
		//cout << "��������ɾ����λ��:" ;
		//while (cin >> n) {
			while (0) {
			if (linked_list_delete_site(L, n)) {
				cout << "�ѳɹ�ɾ����" << n << "λ�õĿռ�\n";
				single_linked_list_output(L);
			}
			else {
				cout << "û�д�λ�õĿռ�,���ٴ�����\n";
				single_linked_list_output(L);
			}
			cout << "��������ɾ����λ��:";
		}

		//��Ԫ������ɾ��
		//cout << "��������ɾ����Ԫ��:";
		//while (cin >> n) {
			while (0) {
			if (linked_list_delete_data(L, n)) {
				cout << "�ѳɹ�ɾ��Ϊ " << n << " ��Ԫ�ؿռ�\n";
				single_linked_list_output(L);
			}
			else {
				cout << "û�д�Ԫ��,���ٴ�����\n";
				single_linked_list_output(L);
			}
			cout << "��������ɾ����λ��:";
		}

		//���ٵ�����
		linked_list_delete(L);
}