#pragma once
#include <stdio.h>
#include <assert.h>
#include <Windows.h> 
#include <iostream> 
#include <iomanip> 
using namespace std;

#define MaxSize 1024 //队列的最大容量

typedef struct _Bnode {
	char value;//保存的字符
	int weight;//频率 //权值 //字符所出现的频率
	struct _Bnode* parent;//父
	struct _Bnode* lchild;//左
	struct _Bnode* rchild;//右
} Btree, Bnode;/* 结点结构体 */ 

typedef Bnode* DataType; //任务队列中元素类型 
typedef struct _QNode { //结点结构 
	int priority; //每个节点的优先级,数值越大，优先级越高，优先级相同， 取第一个节点
	DataType data; 
	struct _QNode *next; 
}QNode; 

typedef QNode * QueuePtr; 
typedef struct Queue { 
	int length; //队列的长度
	QueuePtr front; //队头指针
	QueuePtr rear; //队尾指针 
}LinkQueue;//队列

//队列初始化，将队列初始化为空队列
void InitQueue(LinkQueue* LQ) {
	if (!LQ) return;
	LQ->length = 0;
	LQ->front = LQ->rear = NULL; //把对头和队尾指针同时置 0 
}

//判断队列为空 
int IsEmpty(LinkQueue *LQ) { 
	if(!LQ) return 0; 
	if (LQ->front == NULL) { 
		return 1; 
	}
	return 0;
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
int EnterQueue(LinkQueue* LQ, DataType data, int priority) {
	if (!LQ) return 0;
	if (IsFull(LQ)) {
		cout << "无法插入元素 " << data << ", 队列已满!" << endl;
		return 0;
	}
	QNode* qNode = new QNode;
	qNode->data = data;
	qNode->priority = priority;
	qNode->next = NULL;

	if (IsEmpty(LQ)) {//空队列 
		LQ->front = LQ->rear = qNode;
	}
	else {
		qNode->next = LQ->front;
		LQ->front = qNode;
		//LQ->rear->next =qNode;
		//在队尾插入节点 qNode
		//LQ->rear = qNode;
		//队尾指向新插入的节点
	}
	LQ->length++; return 1;
}

//出队，遍历队列，找到队列中优先级最高的元素 data 出队 
int PopQueue(LinkQueue* LQ, DataType* data) {
	QNode** prev = NULL, * prev_node = NULL;//保存当前已选举的最高优先级节 点上一个节点的指针地址。
	QNode* last = NULL, * tmp = NULL;
	if (!LQ || IsEmpty(LQ)) {
		cout << "队列为空！" << endl;
		return 0;
	}
	if (!data) return 0;
	//prev 指向队头 front 指针的地址 
	prev = &(LQ->front);
	//printf("第一个节点的优先级: %d\n", (*prev)->priority);
	last = LQ->front;
	tmp = last->next;
	while (tmp) {
		if (tmp->priority < (*prev)->priority) {
			//printf("抓到个更小优先级的节点[priority: %d]\n", tmp->priority);
			prev = &(last->next);
			prev_node = last;
		}
		last = tmp;
		tmp = tmp->next;
	}
	*data = (*prev)->data;
	tmp = *prev;
	*prev = (*prev)->next;
	delete tmp; LQ->length--;
	//接下来存在 2 种情况需要分别对待 
	//1.删除的是首节点,而且队列长度为零 
	if (LQ->length == 0) {
		LQ->rear = NULL;
	}
	//2.删除的是尾部节点 
	if (prev_node && prev_node->next == NULL) {
		LQ->rear = prev_node;
	}
	return 1;
}

//打印队列中的各元素 
void PrintQueue(LinkQueue* LQ) {
	QueuePtr tmp;
	if (!LQ) return;
	if (LQ->front == NULL) {
		cout << "队列为空！";
		return;
	}
	tmp = LQ->front;
	while (tmp) {
		cout << setw(4) << tmp->data->value << "[" << tmp->priority << "]";
		tmp = tmp->next;
	}
	cout << endl;
}

//获取队首元素，不出队 
int GetHead(LinkQueue* LQ, DataType* data) {
	if (!LQ || IsEmpty(LQ)) {
		cout << "队列为空!" << endl;
		return 0;
	}
	if (!data) return 0;
	*data = LQ->front->data;
	return 1;
}

//清空队列 
void ClearQueue(LinkQueue* LQ) {
	if (!LQ) return;
	while (LQ->front) {
		QueuePtr tmp = LQ->front->next;
		delete LQ->front;
		LQ->front = tmp;
	}
	LQ->front = LQ->rear = NULL;
	LQ->length = 0;
}

//获取队列中元素的个数 
int getLength(LinkQueue* LQ) {
	if (!LQ) return 0;
	return LQ->length;
}