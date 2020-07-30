#include <iostream>
#include <Windows.h>
#include <stdlib.h>
using namespace std;

//�����ݽṹ�Ķ��� 
#define DEFAULT_CAPCITY 128

typedef struct _Heap {
	int* arr; //�洢��Ԫ�ص����� 
	int size; //��ǰ�Ѵ洢��Ԫ�ظ��� 
	int capacity; //��ǰ�洢������ 
}Heap; 

//��(���)��: 

//��ʼ��(�ѵ�����,Ҫ���������,����Ĵ�С);
bool initHeap(Heap &heap, int *orginal, int size); 
//����,�����溯������ʼ��������������Ž��ѽṹ,��Ϊ����;
static void buildHeap(Heap &heap); 
//�ѵ����µ���; /*����ǰ�Ľڵ���ӽڵ����������*/ 
static void adjustDown(Heap &heap, int index); 

/*����ǰ�Ľڵ�͸��ڵ����������*/
void adjustUp(Heap& heap, int index);

/*����β������ڵ㣬ͬʱ��֤���ѵ�����*/ 
bool insert(Heap& heap, int value);

//���Ԫ�س���//ɾ�����Ľڵ㲢��ýڵ��ֵ
bool popMax(Heap& heap, int& value);

int main(void) {
	Heap Hp;
	int origVals[] = { 1,2,3,87,93,82,92,86,95 };

	
	cout << "sizeof(origVals):" << sizeof(origVals) << endl;
	cout << "sizeof(origVals) / sizeof(origVals[0]):" << sizeof(origVals) / sizeof(origVals[0]) << endl;
	if (! initHeap(Hp, origVals, sizeof(origVals) / sizeof(origVals[0]))) {
		//��׼����豸(����̨,�������);
		fprintf(stderr, "��ʼ�����ǰ�!\n");
		exit(-1);
	}

	for (int i = 0; i < Hp.size; i++) {
		printf("the %dth element : %d\n", i, Hp.arr[i]);
	}

	insert(Hp, 99);
	printf_s("�ڶ��в������Ԫ�� 99. ������:\n");
	for (int i = 0; i < Hp.size; i++) {
		printf("the %dth element : %d\n", i, Hp.arr[i]);
	}

	//����Ԫ�س���
	printf_s("���Ԫ�����γ���:\n");
		int value=0;
		while(popMax(Hp, value)) {
			printf_s("%d  ", value);
		}

	system("pause");
	return 0;
}

/*��ʼ����()*/ 
bool initHeap(Heap &heap, int *orginal, int size){ 
	int capacity = DEFAULT_CAPCITY>size ? DEFAULT_CAPCITY:size; //ȷ��������С
	heap.arr = new int[capacity];//����ռ�
	if(!heap.arr) return false; //����ռ��Ƿ�ɹ�
	heap.capacity = capacity; 
	heap.size = 0; 

	cout << "size*sizeof(int):" << size * sizeof(int)<< endl;

	//��ʽһ:ֱ�ӵ�������Ԫ��
	/*
	//�������ԭʼ�����򹹽��� 
	if(size>0){ 
		//����ֵ,������,���������ֽ���
		memcpy(heap.arr, orginal, size*sizeof(int));//��������;
		heap.size = size; 
		buildHeap(heap); 
	}else { 
		heap.size = 0; 
	}
	*/

	//��ʽ��:һ�β���һ��
	if (size > 0) {
		for (int i = 0; i < size; i++) {
			insert(heap, orginal[i]);
		}
	}


	return true;
}

/*����ǰ�ĸ��ڵ���ӽڵ����������*/ 
void adjustDown(Heap &heap, int index) { 
	int cur=heap.arr[index];//���ڵ�����,���һ��Ҷ�ӽڵ�ĸ��ڵ�λ�ÿ�ʼ
	
	//��ǰ�������Ľڵ� 
	int parent,child; 
	
	/*�жϷ���ڴ��ڵ�ǰ�ڵ��ӽڵ㣬��������� ����ѱ�����ƽ���,����Ҫ������
	������ڣ��������ӽڵ���֮�������������������ӽڵ㻹
	���ӽڵ㣬��Ҫ��������ͬ���Ĳ��������ӽڵ���е��� */ 
	for (parent = index; (parent * 2 + 1) < heap.size; parent = child) {//��֤������,��Խ��;(parent * 2 + 1) < heap.size
		child = parent * 2 + 1;//���һ�����ӽڵ�

		//ȡ�����ӽڵ��е����Ľڵ� 
		//if(�Ƿ�������ӽڵ� && ��<��) //������û�ҵ�,����λ�������Ľڵ�
		if(((child+1)<heap.size)&&(heap.arr[child]<heap.arr[child+1])){ 
			child++; 
		}
		
		//�ж����Ľڵ��Ƿ���ڵ�ǰ�ĸ��ڵ� 
		if(cur>=heap.arr[child]){
			//�����ڣ�����Ҫ����������ѭ�� 
			break; 
		}else {
			//���ڵ�ǰ�ĸ��ڵ㣬���н�����Ȼ����ӽڵ�λ�ü������µ� �� 
			heap.arr[parent]=heap.arr[child]; 
			heap.arr[child]=cur; } 
	} 

	//ѭ�����������½ڵ㿴���Ƿ���������Ľڵ�,�Ӷ���֤��һ������
	//���Ƶݹ�
}

/* �����һ�����ڵ�(size/2-1 ��λ��)�����ǰ�������и��ڵ㣨ֱ������ �㣩,
ȷ��ÿһ�����ڵ㶼��һ�����ѣ�����������γ�һ������ */
void buildHeap(Heap &heap){ 
	int i; 
	
	for(i=heap.size/2-1; i>=0; i--){ //heap.size/2-1;���һ��Ҷ�ӽڵ�ĸ��ڵ�λ�ÿ�ʼ
		adjustDown(heap, i); //�ѽ���,���ڵ�λ�ý���
	} 
}

void adjustUp(Heap& heap, int index) {
	if (index < 0 || index >= heap.size) {//���ڶѵ����ֱֵ�� return 
		return;
	}

	while (index > 0) {
		int temp = heap.arr[index];//��¼����
		int parent = (index - 1) / 2;//���ڵ�λ��
		if (parent >= 0) {//�������û�г����ִ����Ҫ�Ĳ��� 
			if (temp > heap.arr[parent]) { //�ӽڵ�>���ڵ�
				heap.arr[index] = heap.arr[parent];
				heap.arr[parent] = temp;
				index = parent; //������
			}
			else {//����Ѿ��ȸ���С ֱ�ӽ���ѭ��
				break;
			}
		}
		else {//Խ�����ѭ�� 
			break;
		}
	}
}

bool insert(Heap& heap, int value) {
	if (heap.size == heap.capacity) {
		fprintf(stderr, "ջ�ռ�ľ���\n");
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
	//heap.size--;//�����к�����һ��ͬ��
	adjustDown(heap, 0);
	return true;
}