#pragma once
#include <iostream>
#include <Windows.h>
#include <iomanip>
using namespace std;

#define MaxSize 5 //���е�������� 

typedef int DataType; //������Ԫ������ 
typedef struct Queue { 
	DataType queue[MaxSize]; 
	int front; //��ͷλ��
	int rear; //��βλ�� 
}SeqQueue;

//���г�ʼ���������г�ʼ��Ϊ�ն��� 
void InitQueue(SeqQueue *SQ) { 
	if(!SQ) return ; 
	SQ->front = SQ->rear = 0; //�Ѷ�ͷ�Ͷ�βָ��ͬʱ�� 0 
}

//�ж϶����Ƿ�Ϊ�� 
int IsFull(SeqQueue *SQ) { 
	if(!SQ) return 0; 
	if (SQ->rear == MaxSize) { return 1; }
	return 0; 
}

//�ж϶���Ϊ�� 
int IsEmpty(SeqQueue *SQ) { 
	if(!SQ) return 0; 
	if (SQ->front == SQ->rear) {return 1; }
	return 0; 
}

//���,��Ԫ�� data ���뵽���� SQ �� 
int EnterQueue( SeqQueue *SQ,DataType data){ 
	if(!SQ) return 0; 
	if(IsFull(SQ)){ 
		cout<<"�޷�����Ԫ�� "<<data<<", ��������!"<<endl; 
		return 0; 
	}
	SQ->queue[SQ->rear] = data; //�ڶ�β����Ԫ�� data 
	SQ->rear++; //��βָ�����һλ 
		return 1; 
}

//��ӡ�����еĸ�Ԫ�� 
void PrintQueue(SeqQueue* SQ) { 
	if(!SQ) return ; 
	int i = SQ->front; 
	while(i<SQ->rear) { 
		cout<<setw(4)<<SQ->queue[i]; 
		i++; 
	}
	cout<<endl; 
}

//��ʽ 1 - ɾ�� front ��ָ��Ԫ��, ��������Ԫ��ǰ�� 1 �����ر�ɾ��Ԫ��
//���ӣ��������ж�ͷ��Ԫ�� data ���ӣ������Ԫ����ǰ�ƶ� 
int DeleteQueue(SeqQueue* SQ, DataType *data){ 
	if(!SQ || IsEmpty(SQ)){ 
		cout<<"����Ϊ�գ�"<<endl; return 0;
	}
	if(!data) return 0; 
	*data = SQ->queue[SQ->front]; 
	for(int i=SQ->front+1; i<SQ->rear; i++){//�ƶ������Ԫ�� 
		SQ->queue[i-1]=SQ->queue[i]; 
	}
	SQ->rear--;//��βָ��ǰ��һλ 
	return 1; 
}

//���ӣ���ʽ 2 - ɾ�� front ��ָ��Ԫ�أ�Ȼ��� 1 �����ر�ɾԪ�ء�8979438401111 
//���ӣ��������ж�ͷ��Ԫ�� data ���ӣ����Ӻ��ͷָ�� front ����һλ 
int DeleteQueue2(SeqQueue* SQ,DataType* data) { 
	if (!SQ || IsEmpty(SQ)) { 
		cout<<"����Ϊ�գ�"<<endl; return 0; 
	}
	if(SQ->front>=MaxSize){ 
		cout<<"�����ѵ���ͷ!"<<endl; return 0; 
	}
	*data = SQ->queue[SQ->front]; //����Ԫ��ֵ 
	SQ->front = (SQ->front)+1; //����ָ�����һλ 
	return 1; 
}

//��ȡ����Ԫ�أ������� 
int GetHead(SeqQueue* SQ,DataType* data) { 
	if (!SQ || IsEmpty(SQ)) { 
		cout<<"����Ϊ��!"<<endl; 
	}
	*data = SQ->queue[SQ->front];
	if (data == NULL) {
		return NULL;
	}
	return *data;
}

//��ն��� 
void ClearQueue(SeqQueue* SQ) { 
	if(!SQ) return ; 
	SQ->front = SQ->rear = 0; 
}

//��ȡ������Ԫ�صĸ��� 
int getLength(SeqQueue* SQ){
	if(!SQ) return 0; 
	return SQ->rear-SQ->front;
}

void ����_˳��洢() {
	SeqQueue* SQ = new SeqQueue;//���пռ�

	DataType data = 0;//����

	InitQueue(SQ);//��ʼ������

	//���
	for (int i = 1; i <= 7; i++) {
		EnterQueue(SQ, i);
	}

	PrintQueue(SQ);

	//����
	//for(int i=0; i<10; i++){ 
	if (DeleteQueue2(SQ, &data)) {
		cout << "���ӵ�Ԫ���ǣ�" << data << endl;
	}
	else { cout << "����ʧ�ܣ�" << endl; }
	//} 

	//��ӡ�����е�Ԫ�� 
	printf("����һ��Ԫ�غ󣬶�����ʣ�µ�Ԫ�أ�");
	PrintQueue(SQ);
	cout << endl;
}