#pragma once
#include <iostream>
#include <Windows.h>
#include <iomanip>
using namespace std;
#define MaxSize 5 //队列的最大容量
typedef int DataType; //队列中元素类型 
typedef struct _QNode { //结点结构 
	DataType data;
	struct _QNode *next; 
}QNode; 

typedef QNode * QueuePtr; 
typedef struct Queue { 
	int length; //队列的长度 
	QueuePtr front; //队头指针 
	QueuePtr rear; //队尾指针 
}LinkQueue;

//队列初始化，将队列初始化为空队列 
void InitQueue(LinkQueue *LQ) { 
	if(!LQ) return ; 
	LQ->length = 0; 
	LQ->front = LQ->rear = NULL; //把对头和队尾指针同时置 0 
}

//判断队列为空 
int IsEmpty(LinkQueue *LQ) { 
	if(!LQ) return 0; 
	if (LQ->front == NULL)
	{
		return 1;
	}return 0;
}

//判断队列是否为满 
int IsFull(LinkQueue *LQ) { 
	if(!LQ) return 0; 
	if (LQ->length == MaxSize) { 
		return 1; 
	}
	return 0; 
}

//入队,将元素 data 插入到队列 LQ 中 
int EnterQueue( LinkQueue *LQ,DataType data){ 
	if(!LQ) return 0; 
	if(IsFull(LQ)){ 
		cout<<"无法插入元素 "<<data<<", 队列已满!"<<endl; 
		return 0; 
	}
	QNode *qNode = new QNode; 
	qNode->data = data; 
	qNode->next = NULL; 
	if(IsEmpty(LQ)){//空队列 
		LQ->front = LQ->rear = qNode; 
	}else { 
		LQ->rear->next =qNode;//在队尾插入节点 qNode 
		LQ->rear = qNode; //队尾指向新插入的节点 
	}
	LQ->length++; 
	return 1;
}

//出队，将队列中队头的元素出队，其后的第一个元素成为新的队首 
int DeleteQueue(LinkQueue *LQ, DataType *data){ 
	if (!LQ || IsEmpty(LQ)) { 
		cout << "队列为空！" << endl; 
		return 0; 
	}
	if (!data) return 0;
	QNode* tmp = LQ->front;//tmp变身为队头空间
	LQ->front = tmp->next; //原队头空间后移
	if (!LQ->front) LQ->rear = NULL;//如果对头出列后不存在其他元素，则 rear 节点也要置空 
	*data = tmp->data; 
	LQ->length--; 
	delete tmp; 
	return 1; 
}

//打印队列中的各元素 
void PrintQueue(LinkQueue *LQ) { 
	QueuePtr tmp; 
	if(!LQ) return ; 
	if(LQ->front==NULL){
		cout<<"队列为空！"; 
		return ; 
	}
	tmp = LQ->front;
	while(tmp) { 
		cout<<setw(4)<<tmp->data;
		tmp = tmp->next; 
	}
	cout<<endl; 
}

//获取队首元素，不出队 
int GetHead(LinkQueue *LQ,DataType *data) { 
	if (!LQ || IsEmpty(LQ)) { 
		cout << "队列为空!" << endl;
		return 0; 
	}
	if (!data) return 0; 
	*data = LQ->front->data; 
	return 1;
}

//清空队列
void ClearQueue(LinkQueue *LQ) { 
	if(!LQ) return ; 
	QueuePtr tmp = NULL;
	while(LQ->front){
		tmp = LQ->front->next;
		delete LQ->front; 
		LQ->front = tmp; 
	}
	LQ->rear = NULL;
	LQ->length = 0;
}

//获取队列中元素的个数 
int getLength(LinkQueue* LQ){ 
	if(!LQ) return 0; 
	return LQ->length;
}

void 队列_链式存储() {
	LinkQueue* LQ = new LinkQueue; 
	DataType data = -1; 
	//初始化队列 
	InitQueue(LQ); 
	//入队 
	for(int i=0; i<7; i++){ 
		EnterQueue(LQ, i); 
	}
	
	//打印队列中的元素
	printf("队列中的元素(总共%d 个)：", getLength(LQ));
	PrintQueue(LQ); 
	cout << endl; 

	//出队 
	//for(int i=0; i<10; i++){ 
	if(DeleteQueue(LQ, &data)){ 
		cout<<"出队的元素是："<<data<<endl;
	}else { cout<<"出队失败！"<<endl; } 
	//} 
	
	//打印队列中的元素 
	printf("出队一个元素后，队列中剩下的元素[%d]：", getLength(LQ)); 
	PrintQueue(LQ); 
	cout<<endl; 
	ClearQueue(LQ);
	cout<<"清空队列!\n";
	PrintQueue(LQ); 

	//清理资源 
	delete LQ; 
}