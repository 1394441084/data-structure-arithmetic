#pragma once
#include <iostream>
#include <Windows.h>
#include <iomanip>
using namespace std;
#define MaxSize 5 //队列的最大容量
typedef int DataType; //队列中元素类型 
typedef struct _QNode { //结点结构 
	int priority;//每个节点的优先级,0最低级,9最高级,优先级相同取第一个节点 
	DataType data;
	struct _QNode* next;
}QNode;

typedef QNode* QueuePtr;
typedef struct Queue {
	int length; //队列的长度 
	QueuePtr front; //队头指针 
	QueuePtr rear; //队尾指针 
}LinkQueue;

//队列初始化，将队列初始化为空队列 
void InitQueue(LinkQueue* LQ) {
	if (!LQ) return;
	LQ->length = 0;
	LQ->front = LQ->rear = NULL; //把对头和队尾指针同时置 0 
}

//判断队列为空 
int IsEmpty(LinkQueue* LQ) {
	if (!LQ) return 0;
	if (LQ->front == NULL)
	{
		return 1;
	}return 0;
}

//判断队列是否为满 
int IsFull(LinkQueue* LQ) {
	if (!LQ) return 0;
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
	qNode->next = NULL;
	qNode->priority = priority;
	if (IsEmpty(LQ)) {//空队列 
		LQ->front = LQ->rear = qNode;
	}
	else {
		LQ->rear->next = qNode;//在队尾插入节点 qNode 
		LQ->rear = qNode; //队尾指向新插入的节点 
	}
	LQ->length++;
	return 1;
}

//出队，遍历队列，找到队列中优先级最高的元素 data 出队 
int DeleteQueue(LinkQueue *LQ, DataType *data){ 
	QNode **prev = NULL, *prev_node=NULL;//保存当前已选举的最高优先级节点上一个节点的指针地址。
	QNode * last = NULL, *tmp = NULL; //为了遍历整个链表

	if (!LQ || IsEmpty(LQ)) { 
		cout << "队列为空！" << endl; return 0; 
	}
	if (!data) return 0;//数据为空

	prev = &(LQ->front);//prev 指向队头 front 指针的地址 (就队头的next指针)
	printf("第一个节点的优先级: %d\n", (*prev)->priority); 
	last = LQ->front;//指向队头(1)
	tmp = last->next; //指向火车车厢(2)
	while(tmp){ 
		if(tmp->priority >(*prev)->priority){ //比较(火车[2]>火车[1])的优先级
			printf("抓到个更大优先级的节点[priority: %d]\n", tmp->priority); 
			prev = &(last->next); //指向下一个节点(1的next);last->next相当目前的tmp //指向了优先级最高的节点的上一个节点的next地址
			prev_node= last;//指向上一个节点(1) //指向了最高优先级的上一个地址
		}
		last=tmp; //往下移动
		tmp=tmp->next;//往下移动
	}
	//出来后tmp就是NULL了
	*data = (*prev)->data;
	tmp = *prev; //tmp指向了最高优先级节点的上一个节点的next节点 //指向最高优先级节点
	*prev = (*prev)->next;//将最高优先级节点的上一个节点的next指向最高优先级节点的下一个(next)节点
	delete tmp; //将最高优先级节点的空间释放
	LQ->length--; //最高优先级节点已出队,空间长度减一

	//接下来存在 2 种情况需要分别对待 
	//1.删除的是首节点,而且队列长度为零 
	if(LQ->length==0){
		LQ->rear=NULL; 
	}

	//2.删除的是尾部节点 
	if(prev_node && prev_node->next==NULL){ //原队尾已经没有了,所以重新指向
		LQ->rear=prev_node;//队尾指针指向原队尾的上一个节点
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
		cout << setw(4) << tmp->data;
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
	QueuePtr tmp = NULL;
	while (LQ->front) {
		tmp = LQ->front->next;
		delete LQ->front;
		LQ->front = tmp;
	}
	LQ->rear = NULL;
	LQ->length = 0;
}

//获取队列中元素的个数 
int getLength(LinkQueue* LQ) {
	if (!LQ) return 0;
	return LQ->length;
}

void 队列_链式存储() {
	LinkQueue* LQ = new LinkQueue; 
	DataType data = -1; //初始化队列 
	InitQueue(LQ); 
	//入队 
	for(int i=0; i<5; i++){ 
		EnterQueue(LQ, i+10, i);
	}
	
	//打印队列中的元素 
	printf("队列中的元素(总共%d 个)：", getLength(LQ)); 
	PrintQueue(LQ); 
	cout<<endl; 

	//出队 
	for(int i=0; i<5; i++){ 
		if(DeleteQueue(LQ, &data)){ 
			cout<<"出队的元素是："<<data<<endl;
		}else { 
			cout<<"出队失败！"<<endl; 
		} 
	}
	
	//打印队列中的元素 
	printf("出队五个元素后，队列中剩下的元素[%d]：\n", getLength(LQ));
	PrintQueue(LQ); 
	cout<<endl; 
	ClearQueue(LQ);
	cout<<"清空队列!\n"; 
	PrintQueue(LQ);

	//清理资源 
	delete LQ;
}
