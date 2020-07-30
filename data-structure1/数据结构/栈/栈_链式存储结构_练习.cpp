#include <iostream>
#include <stdlib.h>

using namespace std;

typedef int ElemType;
typedef struct _structNode {//����ʵ�ֲ���
	ElemType *data = NULL;//�ڵ�����//�����Ŀռ�
	_structNode* next = NULL;//��һ������ڵ�
}linklist, structNode;//�����׽ڵ�,����ڵ�;//������������

//��ʼ��
bool Initlist(linklist*& L) {//ֻ��ʼ��ͷ�ڵ�
	L = new structNode;//����һ���ڵ�

	if (!L)return false;//���ɽڵ�ʧ��
	L->data = NULL;
	L->next = NULL;//���ڵ���ΪNULL
	return true;//��ʼ���ɹ�
}

//��巨()
bool inser_back(linklist*& L, ElemType* e) {
	structNode* node=new structNode;//����һ���ռ�
	if (!L || !e || !node)return false;//�ж��Ƿ�Ϊ��
	structNode* last = L;//β��
	while (last->next) {
		last = last->next;
	}//������ָ��β���ڵ���

	node->next = NULL;//��β�ڵ�->next��ΪNULL
	node->data = e;
	last->next = node;//β�ڵ�->nextָ���½ڵ�,�½ڵ��Ϊ��β�ڵ�
	return true;
}

//������ȡֵ
bool linked_list_value(linklist*& L, ElemType &e) {
	if (!L || !L->next)return false;//�ж��Ƿ�Ϊ��
	structNode* last = L->next;
	
	while (last->next) {
		last = last->next;
	}//������ָ�����ڵ�
	e = *(last->data);
	return true;
}

//���������
bool linked_list_delete_data(linklist*& L, ElemType &data) {
	if (!L || !L->next) { return false; }//�ж��Ƿ�Ϊ��
	structNode* last = L;

	while (last) {
		if (last->next->next == NULL) {//��ʱ�����һ���ڵ�
			data = *(last->next->data);//�����ݳ�������
			delete last->next->data;//��Ϊdata�����Ҳ��һ���ռ�,����Ҳ��Ҫdelete��
			delete last->next;
			last->next = NULL;
			return true;
		}
		last = last->next;
	}

	return false;
}

//���ٵ�����
void linked_list_delete(linklist*& L) {
	structNode* last = L;
	while (last) {
		L = L->next;//ָ����һ���ڵ�
		//cout << "ɾ��Ԫ��:" << last->data << endl;
		delete last->data;
		delete last;//ɾ��ͷ�ڵ�
		last = L;
	}
}

//���������
void single_linked_list_output(linklist*& L) {
	if (!L) {
		cout << "������Ϊ��\n";
		return;
	}
	structNode* p = L->next;

	while (p) {
		cout << *(p->data) << "\t";
		p = p->next;
	}
	cout << endl;
}

int main() {
	linklist* L = NULL;//�����׽ڵ�
	Initlist(L);//��ʼ��һ���յ�����

	//ʹ�ú�巨��������
	int n; ElemType* s = NULL;
	cout << "��������ջ\n";
	cout << "������Ԫ�ظ���:";
	cin >> n;
	cout << "\n����������" << n << "��Ԫ��:\n";
	while (n > 0) {
		s = new ElemType;//�����½ڵ�
		cin >> *s;//��������
		inser_back(L, s);//��������
		n--;
	}

	//����������
	single_linked_list_output(L);

	//����ջȡָ
	ElemType v;
	linked_list_value(L, v);
	cout << "���һ��Ԫ������Ϊ:" << v << endl;

	//ջ������
	linked_list_delete_data(L, v);
	cout << "���е�Ԫ������Ϊ:" << v << endl;

	single_linked_list_output(L);

	//���ٵ�����
	linked_list_delete(L);

	system("pause");
	return 0;
}