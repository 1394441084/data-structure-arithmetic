#pragma once
#include <iostream>
#include <Windows.h>
#include <iomanip>
using namespace std;

#define MaxSize 5 //队列的最大容量 

typedef int DataType; //队列中元素类型 
typedef struct Queue {
	DataType queue[MaxSize];
	int front; //队头位置
	int rear; //队尾位置 
}SeqQueue;

//队列初始化，将队列初始化为空队列 
void InitQueue(SeqQueue* SQ) {
	if (!SQ) return;
	SQ->front = SQ->rear = 0; //把对头和队尾指针同时置 0 
}

//判断队列是否为满 
int IsFull(SeqQueue* SQ) {
	if (!SQ) return 0;
	if (((SQ->rear+1)% MaxSize) == SQ->front) { return 1; }
	return 0;
}

//判断队列为空 
int IsEmpty(SeqQueue* SQ) {
	if (!SQ) return 0;
	if (SQ->front == SQ->rear) { return 1; }
	return 0;
}

//入队,将元素 data 插入到队列 SQ 中 
int EnterQueue(SeqQueue* SQ, DataType data) {
	if (!SQ) return 0;
	if (IsFull(SQ)) {
		cout << "无法插入元素 " << data << ", 队列已满!" << endl;
		return 0;
	}
	SQ->queue[SQ->rear] = data; //在队尾插入元素 data 
	SQ->rear=(SQ->rear+1)%MaxSize; //队尾指针循环后移一位 
	return 1;
}

//打印队列中的各元素 
void PrintQueue(SeqQueue* SQ) {
	if (!SQ) return;
	int i = SQ->front;
	while (i != SQ->rear) {
		cout << setw(4) << SQ->queue[i];
		i=(i+1) % MaxSize;
	}
	cout << endl;
}

//出队：方式 2 - 删除 front 所指的元素，然后加 1 并返回被删元素。
//出队，将队列中队头的元素 data 出队，出队后队头指针 front 后移一位 
int DeleteQueue2(SeqQueue* SQ, DataType* data) {
	if (!SQ || IsEmpty(SQ)) {
		cout << "队列为空！" << endl; return 0;
	}
	
	*data = SQ->queue[SQ->front]; //出队元素值 
	SQ->front = (SQ->front + 1)%MaxSize; //队首指针循环后移一位 
	return 1;
}

//获取队首元素，不出队 
int GetHead(SeqQueue* SQ, DataType* data) {
	if (!SQ || IsEmpty(SQ)) {
		cout << "队列为空!" << endl;
	}
	*data = SQ->queue[SQ->front];
	if (data == NULL) {
		return NULL;
	}
	return *data;
}

//清空队列 
void ClearQueue(SeqQueue* SQ) {
	if (!SQ) return;
	SQ->front = SQ->rear = 0;
}

//获取队列中元素的个数 
int getLength(SeqQueue* SQ) {
	if (!SQ) return 0;
	return (SQ->rear - SQ->front + MaxSize) % MaxSize;
}

void 循环队列() {
	SeqQueue* SQ = new SeqQueue;//队列空间

	DataType data = 0;//数据

	InitQueue(SQ);//初始化队列

	//入队
	for (int i = 1; i <= 7; i++) {
		EnterQueue(SQ, i);
	}

	PrintQueue(SQ);

	//出队
	for(int i=0; i<5; i++){ 
	if (DeleteQueue2(SQ, &data)) {
		cout << "出队的元素是：" << data << endl;
	}
	else { cout << "出队失败！" << endl; }
	} 

	//打印队列中的元素 
	printf("出队5个元素后，队列中剩下的元素个数为：%d个", getLength(SQ));
	PrintQueue(SQ);
	cout << endl;
}