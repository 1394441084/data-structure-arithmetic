#pragma once
#include <iostream>
#include <Windows.h>
#include <iomanip>
using namespace std;
#define MaxSize 5 //���е��������
typedef int DataType; //������Ԫ������ 
typedef struct _QNode { //���ṹ 
	int priority;//ÿ���ڵ�����ȼ�,0��ͼ�,9��߼�,���ȼ���ͬȡ��һ���ڵ� 
	DataType data;
	struct _QNode* next;
}QNode;

typedef QNode* QueuePtr;
typedef struct Queue {
	int length; //���еĳ��� 
	QueuePtr front; //��ͷָ�� 
	QueuePtr rear; //��βָ�� 
}LinkQueue;

//���г�ʼ���������г�ʼ��Ϊ�ն��� 
void InitQueue(LinkQueue* LQ) {
	if (!LQ) return;
	LQ->length = 0;
	LQ->front = LQ->rear = NULL; //�Ѷ�ͷ�Ͷ�βָ��ͬʱ�� 0 
}

//�ж϶���Ϊ�� 
int IsEmpty(LinkQueue* LQ) {
	if (!LQ) return 0;
	if (LQ->front == NULL)
	{
		return 1;
	}return 0;
}

//�ж϶����Ƿ�Ϊ�� 
int IsFull(LinkQueue* LQ) {
	if (!LQ) return 0;
	if (LQ->length == MaxSize) {
		return 1;
	}
	return 0;
}

//���,��Ԫ�� data ���뵽���� LQ �� 
int EnterQueue(LinkQueue* LQ, DataType data, int priority) {
	if (!LQ) return 0;
	if (IsFull(LQ)) {
		cout << "�޷�����Ԫ�� " << data << ", ��������!" << endl;
		return 0;
	}
	QNode* qNode = new QNode;
	qNode->data = data;
	qNode->next = NULL;
	qNode->priority = priority;
	if (IsEmpty(LQ)) {//�ն��� 
		LQ->front = LQ->rear = qNode;
	}
	else {
		LQ->rear->next = qNode;//�ڶ�β����ڵ� qNode 
		LQ->rear = qNode; //��βָ���²���Ľڵ� 
	}
	LQ->length++;
	return 1;
}

//���ӣ��������У��ҵ����������ȼ���ߵ�Ԫ�� data ���� 
int DeleteQueue(LinkQueue *LQ, DataType *data){ 
	QNode **prev = NULL, *prev_node=NULL;//���浱ǰ��ѡ�ٵ�������ȼ��ڵ���һ���ڵ��ָ���ַ��
	QNode * last = NULL, *tmp = NULL; //Ϊ�˱�����������

	if (!LQ || IsEmpty(LQ)) { 
		cout << "����Ϊ�գ�" << endl; return 0; 
	}
	if (!data) return 0;//����Ϊ��

	prev = &(LQ->front);//prev ָ���ͷ front ָ��ĵ�ַ (�Ͷ�ͷ��nextָ��)
	printf("��һ���ڵ�����ȼ�: %d\n", (*prev)->priority); 
	last = LQ->front;//ָ���ͷ(1)
	tmp = last->next; //ָ��𳵳���(2)
	while(tmp){ 
		if(tmp->priority >(*prev)->priority){ //�Ƚ�(��[2]>��[1])�����ȼ�
			printf("ץ�����������ȼ��Ľڵ�[priority: %d]\n", tmp->priority); 
			prev = &(last->next); //ָ����һ���ڵ�(1��next);last->next�൱Ŀǰ��tmp //ָ�������ȼ���ߵĽڵ����һ���ڵ��next��ַ
			prev_node= last;//ָ����һ���ڵ�(1) //ָ����������ȼ�����һ����ַ
		}
		last=tmp; //�����ƶ�
		tmp=tmp->next;//�����ƶ�
	}
	//������tmp����NULL��
	*data = (*prev)->data;
	tmp = *prev; //tmpָ����������ȼ��ڵ����һ���ڵ��next�ڵ� //ָ��������ȼ��ڵ�
	*prev = (*prev)->next;//��������ȼ��ڵ����һ���ڵ��nextָ��������ȼ��ڵ����һ��(next)�ڵ�
	delete tmp; //��������ȼ��ڵ�Ŀռ��ͷ�
	LQ->length--; //������ȼ��ڵ��ѳ���,�ռ䳤�ȼ�һ

	//���������� 2 �������Ҫ�ֱ�Դ� 
	//1.ɾ�������׽ڵ�,���Ҷ��г���Ϊ�� 
	if(LQ->length==0){
		LQ->rear=NULL; 
	}

	//2.ɾ������β���ڵ� 
	if(prev_node && prev_node->next==NULL){ //ԭ��β�Ѿ�û����,��������ָ��
		LQ->rear=prev_node;//��βָ��ָ��ԭ��β����һ���ڵ�
	}

	return 1; 
}

//��ӡ�����еĸ�Ԫ�� 
void PrintQueue(LinkQueue* LQ) {
	QueuePtr tmp;
	if (!LQ) return;
	if (LQ->front == NULL) {
		cout << "����Ϊ�գ�";
		return;
	}
	tmp = LQ->front;
	while (tmp) {
		cout << setw(4) << tmp->data;
		tmp = tmp->next;
	}
	cout << endl;
}

//��ȡ����Ԫ�أ������� 
int GetHead(LinkQueue* LQ, DataType* data) {
	if (!LQ || IsEmpty(LQ)) {
		cout << "����Ϊ��!" << endl;
		return 0;
	}
	if (!data) return 0;
	*data = LQ->front->data;
	return 1;
}

//��ն���
void ClearQueue(LinkQueue* LQ) {
	if (!LQ) return;
	QueuePtr tmp = NULL;
	while (LQ->front) {
		tmp = LQ->front->next;
		delete LQ->front;
		LQ->front = tmp;
	}
	LQ->rear = NULL;
	LQ->length = 0;
}

//��ȡ������Ԫ�صĸ��� 
int getLength(LinkQueue* LQ) {
	if (!LQ) return 0;
	return LQ->length;
}

void ����_��ʽ�洢() {
	LinkQueue* LQ = new LinkQueue; 
	DataType data = -1; //��ʼ������ 
	InitQueue(LQ); 
	//��� 
	for(int i=0; i<5; i++){ 
		EnterQueue(LQ, i+10, i);
	}
	
	//��ӡ�����е�Ԫ�� 
	printf("�����е�Ԫ��(�ܹ�%d ��)��", getLength(LQ)); 
	PrintQueue(LQ); 
	cout<<endl; 

	//���� 
	for(int i=0; i<5; i++){ 
		if(DeleteQueue(LQ, &data)){ 
			cout<<"���ӵ�Ԫ���ǣ�"<<data<<endl;
		}else { 
			cout<<"����ʧ�ܣ�"<<endl; 
		} 
	}
	
	//��ӡ�����е�Ԫ�� 
	printf("�������Ԫ�غ󣬶�����ʣ�µ�Ԫ��[%d]��\n", getLength(LQ));
	PrintQueue(LQ); 
	cout<<endl; 
	ClearQueue(LQ);
	cout<<"��ն���!\n"; 
	PrintQueue(LQ);

	//������Դ 
	delete LQ;
}
