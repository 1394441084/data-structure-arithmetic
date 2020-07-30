#include <Windows.h> 
#include <iostream> 
#include <iomanip> 

using namespace std; 

#define MaxSize 1000 //队列的最大容量 
typedef struct _QNode { //任务结点结构 
	int id; 
	void (*handler)(void); //函数指针
	struct _QNode *next; 
}QNode; 

typedef QNode * QueuePtr; 
typedef struct Queue { 
	int length; //队列的长度 
	QueuePtr front; //队头指针 
	QueuePtr rear; //队尾指针 
}LinkQueue; 

//分配线程执行的任务节点 
QueuePtr thread_task_alloc() { 
	QNode *task; 
	task = (QNode *)calloc(1,sizeof(QNode)); //分配一块内存
	if (task == NULL) { 
		return NULL; 
	}
	return task; 
}

//队列初始化，将队列初始化为空队列 
void InitQueue(LinkQueue *LQ) { 
	if(!LQ) return ; 
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
int EnterQueue( LinkQueue *LQ,QNode *node){ 
	if(!LQ || !node) return 0;
	if(IsFull(LQ)){ 
		cout<<"无法插入任务 "<<node->id<<", 队列已满!"<<endl;
		return 0;
	}
	node->next = NULL;
	if(IsEmpty(LQ)){//空队列 
		LQ->front = LQ->rear = node;
	}else {
		LQ->rear->next =node;//在队尾插入节点 qNode 
		LQ->rear = node; //队尾指向新插入的节点 
	}
	LQ->length++; 
	return 1; 
}

 //出队,将队列中队头的节点出队，返回头节点 
QNode * PopQueue(LinkQueue *LQ){ 
	QNode * tmp = NULL; 
	if(!LQ || IsEmpty(LQ)){ 
		cout<<"队列为空！"<<endl; return 0;
	}
	tmp = LQ->front;
	LQ->front = tmp->next;
	if(!LQ->front) LQ->rear=NULL;//如果对头出列后不存在其他元素，则 rear 节点也要置空 
	LQ->length--;
	return tmp; 
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
		cout<<setw(4)<<tmp->id;
		tmp = tmp->next;
	}
	cout<<endl;
}

//获取队列中元素的个数 
int getLength(LinkQueue* LQ){ 
	if(!LQ) return 0; 
	return LQ->length;
}

 void task1() { 
	 printf("我是任务 1 ...\n");
 }
 void task2() {
	 printf("我是任务 2 ...\n");
 }
 
void 任务队列() {
	LinkQueue* LQ = new LinkQueue; 
	QNode* task = NULL;
	
	//初始化队列 
	InitQueue(LQ); 
	
	//任务 1 入队 
	task= thread_task_alloc();
	task->id = 1; 
	task->handler = &task1;
	EnterQueue(LQ, task);
	
	//任务 2 入队 
	task= thread_task_alloc(); 
	task->id = 2;
	task->handler = &task2;
	EnterQueue(LQ, task);
	
	//打印任务队列中的元素
	printf("队列中的元素(总共%d 个)：", getLength(LQ));
	PrintQueue(LQ);
	cout<<endl; 
	
	//执行任务
	while( (task=PopQueue(LQ)) ){ //接收队头空间
		task->handler();
		delete task;//释放空间,变为野指针
	}
	//清理资源 
	delete LQ; 
 }