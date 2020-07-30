#pragma once
#include <iostream>
using namespace std;

//��һ��,�����Ϊ����,���ݳ�Ϊ����
typedef struct _structNode {//����ʵ�ֲ���
	_structNode* up = NULL;
	//int data = NULL;//�ڵ�����
	_structNode* next = NULL;//��һ������ڵ�
}linklist, structNode;//�����׽ڵ�,����ڵ�;//������������Ч����

typedef struct {//ʱ��ṹ�� //���г�ʱ����
	int fd;	//web���ڷ�����    //�ṹ���ַ����,�������4���ֽ����õ�
	time_t timestamp;//��ʱ-ʱ���  //8�ֽ�
	_structNode node;//˫������ڵ�"�Ҽ�"//������ɳ���
}timeDimension;//ʱ��ά��

struct STAR {
	int x; //���ǵ� x ���� 
	int y; //���ǵ� y ���� 
	unsigned radius; //���ǵİ뾶 
	int step; //ÿ����Ծ�ļ�� 
	int color; //���ǵ���ɫ 
	_structNode node;//˫������ڵ�"�Ҽ�"//������ɳ���
};

//�����ʼ��(linklistָ�����͵�����)
bool Initlist(linklist& L) {//��ʼ��ͷ�ڵ�
	L.up = NULL;
	L.next = NULL;//���ڵ���ΪNULL
	return true;//��ʼ���ɹ�
}

//ǰ�巨 (�׽ڵ�,����Ľڵ�)
bool inser_front(linklist*& L, structNode*& node) {
	if (!L || !node)return false;//�ж��Ƿ�Ϊ��
	if(L->next) L->next->up = node;
	node->next = L->next;
	L->next = node;
	node->up = L;
	return true;
}

//β�巨 (�׽ڵ�,����Ľڵ�)
bool inser_back(linklist & L, structNode & node) {
	structNode* last= &L;
	while (last->next) last = last->next;//�ҳ����һ���ڵ�
	node.next = NULL;
	last->next = &node;
	node.up = last;
	return true;
}

/*
//˫���������
void single_linked_list_output(linklist*& L) {
	if (!L || L->next == L) {
		cout << "������Ϊ��\n";
		return;
	}
	structNode* p = L;

	while (p->next) {
		cout << p->next->data << "\t";
		p = p->next;
	}
	cout << endl;

	cout << "�����ӡ:";
	while (p->up) {
		cout << p->data << "\t";
		p = p->up;
	}
	cout << endl;
}

//��ָ��λ�ò���Ԫ��
bool inser(linklist*& L, int i, int e) {
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
	last1->up = last;
	if (last->next) last->next->up = last1;
	last->next = last1;
	
	return true;
}

//��λ��ɾ��Ԫ��
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
	if(last1->next) last1->next->up = last;
	delete last1;
	return true;//���ݶ�����,����
}

//��������
void linked_list_delete(linklist*& L) {
	if (!L) return;
	structNode* last = L;
	while (last) {
		L = L->next;//ָ����һ���ڵ�
		//cout << "ɾ��Ԫ��:" << last->data << endl;
		delete last;//ɾ��ͷ�ڵ�
		last = L;
	}
}

void single_linked_list_main() {
	linklist* L = NULL;//�����׽ڵ�
	if (Initlist(L)) { cout << "��ʼ���ɹ�\n"; }
	else { exit(-1); }//��ʼ��һ���յ�����
	int n = 0; structNode* s = NULL; int x = 0;

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

		single_linked_list_output(L);

		cout << "��巨����������\n";
		cout << "������Ԫ�ظ���:";
		cin >> n;
		cout << "\n����������" << n << "��Ԫ��:\n";

		while (n > 0) {
			s = new structNode;//�����½ڵ�
			cin >> s->data;
			inser_back(L, s);
			--n;
		}

		single_linked_list_output(L);

		//������λ�ò���
		cout << "ָ��λ�ò���Ԫ��\n";
		cout << "���������λ�ú�Ԫ��(�ÿո����):\n";
		while (cin >> n >> x) {
			if (inser(L, n, x)) single_linked_list_output(L);
			else cout << "����ʧ��\n";
		}

		single_linked_list_output(L);


}*/