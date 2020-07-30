#pragma once
#include <iostream>
using namespace std;
//�������:��ٶ��������֪����ɶ��,���Ǹ�������
typedef struct _structNode {//����ʵ�ֲ���
	int data = NULL;//�ڵ�����
	_structNode* next = NULL;//��һ������ڵ�
}linklist, structNode;//�����׽ڵ�,����ڵ�;//������������Ч����

//ѭ�������ʼ��(linklistָ�����͵�����)
bool Initlist(linklist*& L) {//��ʼ��ͷ�ڵ�
	L = new structNode;//����һ���ڵ�

	if (!L)return false;//���ɽڵ�ʧ��

	L->data = NULL;
	L->next = L;//���ڵ���ΪNULL

	return true;//��ʼ���ɹ�
}
/*
//ǰ�巨 (�׽ڵ�,����Ľڵ�)
bool inser_front(linklist*& L, structNode*& node) {
	if (!L || !node)return false;//�ж��Ƿ�Ϊ��

	node->next = L->next;//ԭ�׽ڵ����һ���ڵ��ַ,�ɽ�����,�µ���һ���ڵ�ӹ�
	L->next = node;//�׽ڵ����һ���ڵ��ַ�滻���½ڵ��ַ

	return true;
}*/

//��巨()
bool inser_back(linklist*& L, structNode*& node) {
	if (!L || !node)return false;//�ж��Ƿ�Ϊ��
	
	if (L->next == L) {//�յ�ѭ������
		node->next = L;
		L->next = node;	
	}
	else {
		structNode* last = L->next;
		while (last->next != L){
			last = last->next;
		}//��λ�����һ���ڵ�
		node->next = L;
		last->next = node;//β�ڵ�->nextָ���½ڵ�,�½ڵ��Ϊ��β�ڵ�
	}

	return true;
}
/*
//��ָ��λ�ú����
bool inser(linklist*& L, int i, int& e) {
	if (!L || i <= 0)return false;//�ж��Ƿ�Ϊ��
	i--;//����ǲ�����λ����
	structNode* last = L;
	int j = 0;
	while (last->next && j < i) {
		j++;
		last = last->next;
	}//������ָ���ǽڵ���
	if (!last->next && j < i)return false;//��������λ����

	structNode* last1 = new structNode;//�½ڵ�
	last1->data = e;
	last1->next = last->next;
	last->next = last1;

	return true;
}*/
/*
//������ȡֵ
bool linked_list_value(linklist*& L, int i, int& e) {
	if (!L || !L->next || i <= 0)return false;//�ж��Ƿ�Ϊ��
	structNode* last = L->next;
	int j = 1;

	while (last->next && j < i) {
		j++;
		last = last->next;
	}//������ָ���ǽڵ���

	if (!last->next && j < i)return false;//��������λ����

	e = last->data;

	return true;
}*/
/*
//���������Ԫ��
bool linked_list_search_data(linklist*& L, int data, int& i) {//��ֵ����
	if (!L || !L->next) { i = -1; return false; }//�ж��Ƿ�Ϊ��
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
	if (!L || !L->next) { return false; }//�ж��Ƿ�Ϊ��
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
	if (!L || !L->next || i <= 0) { return false; }//�ж��Ƿ�Ϊ��
	structNode* last = L;

	int j = 1;

	while (last->next && i > j) {
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
}*/

//ѭ���������
void single_linked_list_output(linklist*& L) {
	if (!L || L->next==L) {
		cout << "������Ϊ��\n";
		return;
	}
	structNode* p = L->next;

	while (p != L) {
		cout << p->data << "\t";
		p = p->next;
	}
	cout << endl;
}

bool joseph(linklist*& L, int in) {
	
	//�ж�
		if (!L || L->next == L) {
			cout << "������Ϊ��\n";
			return false;
		}else if (in<1) {//�������С��1
			cout << "������̭�����С��1!\n";
			return false;
		}
	
		linklist *p=L,*q=NULL;
		int j = 0;//i����
		int times=1;//���е��ڼ���
		int num;//��һ�γ�Ȧ��

		do {
			while (p->next){//������������
				if (p->next != L) j++;//��ָ���׽ڵ�ͱ���������ȥ
				if (j >= in) break;//�ҵ��˱���Ϊin�Ľڵ�
				p = p->next;
			}//����ָ��Ҫ���е���һ���ڵ�
			j=0;  

			q = p->next;//Ҫ���еĽڵ�
 			num = q->data;//��Ȧ�ߵ�Ԫ��(���)
			if (times++ == 5)cout << "�������Ȧ�ߵı����:" << num << endl;
			printf("��:%d  ����:%d  ��:%d\n", p->data, q->data, q->next->data);
			p->next = q->next;
			delete q;//ɾ�������нڵ�
			single_linked_list_output(L);
		} while (L->next != L);//����Ϊ�ռ�������
		cout << "����Ȧ��:" << num << endl;
		return true;
		/*
		Joseph����
��10��С���Ѱ����˳��1, 2,��������10˳ʱ�뷽��Χ��һ-Ȧ����1�ſ�
ʼ˳ʱ�뷽��1, 2,����
����9����,������9�߳���(��Ȼ����-����ȦΪ���9��)��
���һ����Ȧ�ߵı���Ƕ���?��5����Ȧ�ߵı���Ƕ���?
		*/
}


void single_linked_list_main() {
	linklist* L = NULL;//�����׽ڵ�
	if (Initlist(L)) {cout << "��ʼ���ɹ�\n";}
	else {exit(-1);}//��ʼ��һ���յ�����
	int n = 0; structNode* s = NULL; int x = 0;

	/*ǰ�巨û���ع�
	//ʹ��ǰ�巨��������
	
	cout << "ǰ�巨����������\n";
	cout << "������Ԫ�ظ���:";
	cin >> n;
	cout << "\n����������" << n << "��Ԫ��:\n";

	while (n > 0) {
		s = new structNode;//�����½ڵ�
		cin >> s->data;
		inser_front(L, s);
		--n;
	}*/

	//ѭ����������
	single_linked_list_output(L);

	//ʹ�ú�巨��������
	//int n; structNode* s = NULL;
	cout << "��巨����������\n";
	cout << "������Ԫ�ظ���:";
	cin >> n;
	cout << "\n����������" << n << "��Ԫ��:\n";

	while ((n--)>0) {
		s = new structNode;//�����½ڵ�
		cin >> s->data;
		inser_back(L, s);
	}
	single_linked_list_output(L);
	
	joseph(L, 9);

	/*
	//������λ�ò���Ԫ��
	for (int i = 0; i < -3; i++) {
		cout << "���������λ�ú�Ԫ��(�ÿո����):\n";
		cin >> n >> x;

		if (inser(L, n, x)) { single_linked_list_output(L); }
		else { cout << "����ʧ��!\n"; }
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
			cout << "Ԫ��: " << n << " ������ĵ�" << x << "λ��." << endl;
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
	//linked_list_delete(L);*/
}