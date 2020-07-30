#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

#define DEFAULT_CAPCITY 128   //堆的默认空间

typedef struct _Task{
	int priority; //降序优先队列
	//其它的状态属性省略
} Task;

#define isLess(a,b) (a.priority<b.priority) 

typedef Task DataType;//自定义类型
//#define isLess(a,b) (a<b) //比较宏函数

typedef struct _PriorityQueue {
	DataType* arr; //存储堆元素的数组 
	int size; //当前已存储的元素个数 
	int capacity; //当前存储的容量 
}PriorityQueue; 

bool init(PriorityQueue &pq, DataType*orginal, int size);/*初始化优先队列*/ 
bool push(PriorityQueue &pq, DataType value); /*优先队列中插入节点*/ 
bool pop(PriorityQueue &pq, DataType &value); /* 删除优先队列中最大的节点，并获得节点的值*/
bool isEmpty(PriorityQueue &pq); /*优先队列是否为空*/ 
bool isFull(PriorityQueue &pq); /*优先队列是否为满*/ 
void destroy(PriorityQueue &pq); /*销毁优先级队列*/

 /* 从最后一个父节点(size/2-1 的位置)逐个往前调整所有父节点（直到根节 点）, 确保每一个父节点都是一个最大堆，最后整体上形成一个最大堆 */
static void build(PriorityQueue &pq);
static void adjustDown(PriorityQueue &pq, int index);/*将当前的节点和子节点调整成最大堆*/
static void adjustUp(PriorityQueue &pq, int index);/*将当前的节点和父节点调整成最大堆*/ 

int main(void) {
	PriorityQueue pq; 
	int task1[] = { 1, 2, 3, 87, 93, 82, 92, 86, 95 };

	int task1size = sizeof(task1) / sizeof(task1[0]);

	Task* task = new Task[task1size];
	for (int i = 0; i < task1size; i++) {
		task[i].priority = task1[i];
	}
	
	if (!init(pq, task, task1size)) {
		fprintf(stderr, "初始化优先队列失败！\n");
		exit(-1);
	}
	for (int i = 0; i < pq.size; i++) {
		printf("the %dth task:%d\n", i, pq.arr[i].priority);
	}

	//堆中插入优先级为 88 的任务 
	Task task2;
	task2.priority = 88;
	push(pq, task2);
	//堆中元素出列 
	printf("按照优先级出列：\n");
	DataType value;
	while (pop(pq, value)) {
		printf(" %d\n", value.priority);
	}
	destroy(pq);
	system("pause");
	return 0;
}

/*初始化优先队列*/ 
bool init(PriorityQueue &pq, DataType *orginal, int size) { 
	int capacity = DEFAULT_CAPCITY>size ? DEFAULT_CAPCITY : size; 
	pq.arr = new DataType[capacity]; 
	if (!pq.arr) return false; 
	pq.capacity = capacity; 
	pq.size = 0; 
	//如果存在原始数据则构建最大堆 
	if(size > 0){ 
		//方式一: 直接调整所有元素
		memcpy(pq.arr, orginal, size*sizeof(DataType));
		pq.size = size; 

		//建堆 
		build(pq);
	}return true; 
}

/*销毁优先级队列*/ 
void destroy(PriorityQueue& pq) { 
	if (pq.arr) delete[] pq.arr;
}

/*优先队列是否为空*/ 
bool isEmpty(PriorityQueue& pq) {
	if (pq.size < 1) return true; 
	return false; 
}

/*优先队列是否为满*/ 
bool isFull(PriorityQueue& pq) { 
	if (pq.size < pq.capacity) return false; 
	return true;
}

int size(PriorityQueue& pq) {
	return pq.size;
}

/* 从最后一个父节点(size/2-1 的位置)逐个往前调整所有父节点（直到根节 点）, 
确保每一个父节点都是一个最大堆，最后整体上形成一个最大堆 */ 
void build(PriorityQueue& pq) { 
	int i; 
	for (i = pq.size / 2 - 1;i >= 0; i--) {
		adjustDown(pq, i); 
	} 
}

/*将当前的节点和子节点调整成最大堆*/
void adjustDown(PriorityQueue& pq, int index) {
		DataType cur = pq.arr[index];//当前待调整的节点 
		int parent, child; 
		/*判断否存在大于当前节点子节点，如果不存在 ，则堆本身是平衡的,不需要调整;
		如果存在，则将最大的子节点与之交换，交换后，如果这个子节点还有子节点，
		则要继续按照同样的步骤对这个子节点进行调整*/ 
		for (parent = index; (parent * 2 + 1) < pq.size; parent = child) {
			child = parent * 2 + 1; 
			//取两个子节点中的最大的节点 
			if (((child + 1)<pq.size) && isLess(pq.arr[child], pq.arr[child + 1])) { child++; }
			//判断最大的节点是否大于当前的父节点 
			if (isLess(pq.arr[child], cur)) {//不大于，则不需要调整，跳出循 环 
			break; 
			}else {//大于当前的父节点，进行交换，然后从子节点位置继续向下调整 
			pq.arr[parent] = pq.arr[child]; 
			pq.arr[child] = cur; 
			}
		} 
}
			
/*将当前的节点和父节点调整成最大堆*/ 
void adjustUp(PriorityQueue &pq, int index) { 
	if(index<0 || index >= pq.size){//大于堆的最大值直接 
		return; 
	}
	while(index>0){ 
		DataType temp = pq.arr[index]; 
		int parent = (index - 1) / 2; 
		if(parent >= 0){//如果索引没有出界就执行想要的操作 
			if( isLess(pq.arr[parent], temp) ){ 
				pq.arr[index] = pq.arr[parent];
				pq.arr[parent] = temp; 
				index = parent; 
			}else {//如果已经比父亲小 直接结束循环 
				break; 
			} 
		}else {//越界结束循环 
			break; 
		} 
	}	
}

/* 删除优先队列中最大的节点，并获得节点的值*/ 
bool pop(PriorityQueue & pq, DataType & value) {
		if (isEmpty(pq)) return false;
		value = pq.arr[0]; 
		pq.arr[0] = pq.arr[--pq.size];
		//heap.arr[0] = heap.arr[heap.size-1]; 
		//heap.size--; 
		adjustDown(pq, 0);//向下执行堆调整 
		return true; 
}

/*优先队列中插入节点*/ 
bool push(PriorityQueue &pq, DataType value) { 
	if (isFull(pq)) { 
		fprintf(stderr, "优先队列空间耗尽！\n");
		return false; 
	}
	int index = pq.size; 
	pq.arr[pq.size++] = value; 
	adjustUp(pq, index);
	return true;
}

