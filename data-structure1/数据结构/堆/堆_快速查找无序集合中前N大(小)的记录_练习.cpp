#include <iostream>
#include <stdlib.h>

using namespace std;

#define HEAP_SPACE 128 //堆的总空间
typedef int CustomType;//自定义类型
typedef struct _HEAP {//堆
	CustomType* array;//数组指针
	int space;//堆的总空间
	int size;//当前存储元素个数
}HEAP;//堆

//树二叉树,建堆的排序算法_下
static void sorting_algorithm_down(HEAP& heap, int i) {//堆,父节点位置
	for (; (i * 2 + 1) < heap.size; i) {//判断是否有左子节点(因为堆特性相当于判断是否有子节点)
		i = i * 2 + 1;
		
		//取最小子节点位置
		if ((i + 1) < heap.size && heap.array[i + 1] < heap.array[i]) {//判断是否有右子节点,而且右<左
			i++;//取最小子节点
		}

		if (heap.array[(i - 1) / 2] < heap.array[i]) {//如果父节点<子节点则无需调整
			break;
		}
		else {
			CustomType tmp = heap.array[(i-1)/2];//暂存父节点数据
			heap.array[(i-1)/2] = heap.array[i];//子节点数据移到父节点
			heap.array[i] = tmp;//父节点数据移到子节点
		}
	}
}

//树二叉树,建堆的排序算法_上
static void sorting_algorithm_up(HEAP& heap,int i) {//堆,新节点(字节点)位置
	if (i < 0 || i >= heap.size)return;
	while (i > 0) {
		if (((i - 1) * 2) >= 0) {//拥有父节点
			if (heap.array[(i - 1) * 2] > heap.array[i]) {//父节点>子节点
				CustomType tmp = heap.array[i];//暂存新节点数据
				heap.array[i] = heap.array[(i - 1) * 2];//子节点数据变更为父节点数据
				heap.array[(i - 1) * 2] = tmp;//父节点数据变更为字节点数据
				i = (i - 1) * 2;//变为父节点
			}
			else {//最小堆则无需变更,跳出循环,避免死循环
				break;
			}
		}
		else {//不拥有父节点,跳出循环,避免死循环
			break;
		}
	}
}

//树二叉树,建堆
/* 从最后一个父节点( (size-1)/2 的位置)逐个往前调整所有父节点（直到根节点）,
确保每一个父节点都是一个最小堆，最后整体上形成一个最小堆 */
static void done(HEAP& heap) {
	int i = (heap.size - 1) / 2;//最尾父节点
	for (; i >=0; i--) {
		sorting_algorithm_down(heap, i);
	}
}

//初始化堆
bool init(HEAP& heap, CustomType* array,int size) {
	//heap.space = size > HEAP_SPACE ? size : HEAP_SPACE;
	//heap.array = new CustomType[size];
	//if (!heap.array)return false;
	//heap.size = 0;
	if (size > 0) {
		//memcpy(heap.array, array, size * sizeof(CustomType));
		heap.array = array;
		heap.size = size;
		done(heap);
		return true;
	}
	return false;
}

//堆插入节点
bool insert(HEAP& heap, CustomType array) {
	if (heap.size < heap.space)return false;//空间超了
	heap.array[heap.size++] = array;//将节点插入
	sorting_algorithm_up(heap,heap.size-1);//调整堆
	return true;
}

//出堆,将最小节点出列并返回
bool come_heap(HEAP& heap, CustomType &array) {
	if (heap.size < 1)return false;
	array = heap.array[0];//出列的节点数据
	heap.array[0] = heap.array[heap.size-1];
	heap.array[heap.size - 1] = array;
	heap.size--;
	sorting_algorithm_down(heap, 0);
	return true;
}

//堆排序
bool heapSort(HEAP& heap) {
	if (heap.size < 1) return false;
	while (heap.size > 0) {
		int tmp = heap.array[0];
		heap.array[0] = heap.array[heap.size - 1];
		heap.array[heap.size - 1] = tmp;
		heap.size--;
		sorting_algorithm_down(heap, 0);// 向下执行堆调整 
	}
	return true;
}

//销毁堆
void deleteHeap(HEAP& heap) {
	if (heap.array) {
		delete[] heap.array;
	}
}

int main(void) {
	HEAP hp;
	int arr[] = { 5,6,88,99,42,1,54,6,97,35,2,3,4,87,8,66,32,47,85,215,35,65,26,24,18 };
	if (!init(hp, arr, sizeof(arr) / sizeof(arr[0]))) {
		fprintf(stderr, "初始化堆失败！\n");
		exit(-1);
	}

	int i = 0; 
	CustomType array=0;
	//查找集合中前N个小的记录
	printf("查找集合中前N个小的记录:\n请输入收集数据的个数:");
	scanf_s("%d", &i);
	while (i-- && come_heap(hp, array)) {
		printf("%d  ", array);
	}
	
	//查找集合中前N个大的记录
	printf("\n查找集合中前N个大的记录:\n请输入收集数据的个数:");
	scanf_s("%d", &i);
	heapSort(hp);
	i = i > sizeof(arr) / sizeof(arr[0]) ? sizeof(arr) / sizeof(arr[0]) : i;
	while (i--) {
		printf(" %d", arr[i]);
	}
	system("pause");
	return 0;
}