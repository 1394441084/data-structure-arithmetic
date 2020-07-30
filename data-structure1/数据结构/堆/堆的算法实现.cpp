#include <iostream>
#include <Windows.h>
#include <stdlib.h>
using namespace std;

//堆数据结构的定义 
#define DEFAULT_CAPCITY 128

typedef struct _Heap {
	int* arr; //存储堆元素的数组 
	int size; //当前已存储的元素个数 
	int capacity; //当前存储的容量 
}Heap; 

//建(最大)堆: 

//初始堆(堆的引用,要排序的数组,数组的大小);
bool initHeap(Heap &heap, int *orginal, int size); 
//建堆,将上面函数所初始化的需排序数组放进堆结构,成为最大堆;
static void buildHeap(Heap &heap); 
//堆的向下调整; /*将当前的节点和子节点调整成最大堆*/ 
static void adjustDown(Heap &heap, int index); 

/*将当前的节点和父节点调整成最大堆*/
void adjustUp(Heap& heap, int index);

/*最大堆尾部插入节点，同时保证最大堆的特性*/ 
bool insert(Heap& heap, int value);

//最大元素出列//删除最大的节点并获得节点的值
bool popMax(Heap& heap, int& value);

int main(void) {
	Heap Hp;
	int origVals[] = { 1,2,3,87,93,82,92,86,95 };

	
	cout << "sizeof(origVals):" << sizeof(origVals) << endl;
	cout << "sizeof(origVals) / sizeof(origVals[0]):" << sizeof(origVals) / sizeof(origVals[0]) << endl;
	if (! initHeap(Hp, origVals, sizeof(origVals) / sizeof(origVals[0]))) {
		//标准输出设备(控制台,输出数据);
		fprintf(stderr, "初始化堆是吧!\n");
		exit(-1);
	}

	for (int i = 0; i < Hp.size; i++) {
		printf("the %dth element : %d\n", i, Hp.arr[i]);
	}

	insert(Hp, 99);
	printf_s("在堆中插入的新元素 99. 插入结果:\n");
	for (int i = 0; i < Hp.size; i++) {
		printf("the %dth element : %d\n", i, Hp.arr[i]);
	}

	//堆中元素出列
	printf_s("最大元素依次出列:\n");
		int value=0;
		while(popMax(Hp, value)) {
			printf_s("%d  ", value);
		}

	system("pause");
	return 0;
}

/*初始化堆()*/ 
bool initHeap(Heap &heap, int *orginal, int size){ 
	int capacity = DEFAULT_CAPCITY>size ? DEFAULT_CAPCITY:size; //确定容量大小
	heap.arr = new int[capacity];//分配空间
	if(!heap.arr) return false; //分配空间是否成功
	heap.capacity = capacity; 
	heap.size = 0; 

	cout << "size*sizeof(int):" << size * sizeof(int)<< endl;

	//方式一:直接调整所有元素
	/*
	//如果存在原始数据则构建堆 
	if(size>0){ 
		//待赋值,被拷贝,被拷贝总字节数
		memcpy(heap.arr, orginal, size*sizeof(int));//拷贝数据;
		heap.size = size; 
		buildHeap(heap); 
	}else { 
		heap.size = 0; 
	}
	*/

	//方式二:一次插入一个
	if (size > 0) {
		for (int i = 0; i < size; i++) {
			insert(heap, orginal[i]);
		}
	}


	return true;
}

/*将当前的父节点和子节点调整成最大堆*/ 
void adjustDown(Heap &heap, int index) { 
	int cur=heap.arr[index];//父节点数据,最后一个叶子节点的父节点位置开始
	
	//当前待调整的节点 
	int parent,child; 
	
	/*判断否存在大于当前节点子节点，如果不存在 ，则堆本身是平衡的,不需要调整；
	如果存在，则将最大的子节点与之交换，交换后，如果这个子节点还
	有子节点，则要继续按照同样的步骤对这个子节点进行调整 */ 
	for (parent = index; (parent * 2 + 1) < heap.size; parent = child) {//保证数组内,不越界;(parent * 2 + 1) < heap.size
		child = parent * 2 + 1;//最后一个左子节点

		//取两个子节点中的最大的节点 
		//if(是否存在右子节点 && 左<右) //不论有没找到,都定位到了最大的节点
		if(((child+1)<heap.size)&&(heap.arr[child]<heap.arr[child+1])){ 
			child++; 
		}
		
		//判断最大的节点是否大于当前的父节点 
		if(cur>=heap.arr[child]){
			//不大于，则不需要调整，跳出循环 
			break; 
		}else {
			//大于当前的父节点，进行交换，然后从子节点位置继续向下调 整 
			heap.arr[parent]=heap.arr[child]; 
			heap.arr[child]=cur; } 
	} 

	//循环就是再往下节点看看是否有需调整的节点,从而保证是一个最大堆
	//类似递归
}

/* 从最后一个父节点(size/2-1 的位置)逐个往前调整所有父节点（直到根节 点）,
确保每一个父节点都是一个最大堆，最后整体上形成一个最大堆 */
void buildHeap(Heap &heap){ 
	int i; 
	
	for(i=heap.size/2-1; i>=0; i--){ //heap.size/2-1;最后一个叶子节点的父节点位置开始
		adjustDown(heap, i); //堆进入,父节点位置进入
	} 
}

void adjustUp(Heap& heap, int index) {
	if (index < 0 || index >= heap.size) {//大于堆的最大值直接 return 
		return;
	}

	while (index > 0) {
		int temp = heap.arr[index];//记录数据
		int parent = (index - 1) / 2;//父节点位置
		if (parent >= 0) {//如果索引没有出界就执行想要的操作 
			if (temp > heap.arr[parent]) { //子节点>父节点
				heap.arr[index] = heap.arr[parent];
				heap.arr[parent] = temp;
				index = parent; //往上走
			}
			else {//如果已经比父亲小 直接结束循环
				break;
			}
		}
		else {//越界结束循环 
			break;
		}
	}
}

bool insert(Heap& heap, int value) {
	if (heap.size == heap.capacity) {
		fprintf(stderr, "栈空间耗尽！\n");
		return false;
	}
	int index = heap.size;
	heap.arr[heap.size++] = value;
	adjustUp(heap, index);
	return true;
}

bool popMax(Heap& heap, int& value) {
	if (heap.size < 1) return false; 

	value = heap.arr[0];

	heap.arr[0] = heap.arr[--heap.size];
	//heap.arr[0] = heap.arr[heap.size-1];
	//heap.size--;//这两行和上面一行同理
	adjustDown(heap, 0);
	return true;
}