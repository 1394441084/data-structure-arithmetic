#include <iostream>
#include <stdlib.h>

using namespace std;

#define HEAP_SPACE 128 //�ѵ��ܿռ�
typedef int CustomType;//�Զ�������
typedef struct _HEAP {//��
	CustomType* array;//����ָ��
	int space;//�ѵ��ܿռ�
	int size;//��ǰ�洢Ԫ�ظ���
}HEAP;//��

//��������,���ѵ������㷨_��
static void sorting_algorithm_down(HEAP& heap, int i) {//��,���ڵ�λ��
	for (; (i * 2 + 1) < heap.size; i) {//�ж��Ƿ������ӽڵ�(��Ϊ�������൱���ж��Ƿ����ӽڵ�)
		i = i * 2 + 1;
		
		//ȡ��С�ӽڵ�λ��
		if ((i + 1) < heap.size && heap.array[i + 1] < heap.array[i]) {//�ж��Ƿ������ӽڵ�,������<��
			i++;//ȡ��С�ӽڵ�
		}

		if (heap.array[(i - 1) / 2] < heap.array[i]) {//������ڵ�<�ӽڵ����������
			break;
		}
		else {
			CustomType tmp = heap.array[(i-1)/2];//�ݴ游�ڵ�����
			heap.array[(i-1)/2] = heap.array[i];//�ӽڵ������Ƶ����ڵ�
			heap.array[i] = tmp;//���ڵ������Ƶ��ӽڵ�
		}
	}
}

//��������,���ѵ������㷨_��
static void sorting_algorithm_up(HEAP& heap,int i) {//��,�½ڵ�(�ֽڵ�)λ��
	if (i < 0 || i >= heap.size)return;
	while (i > 0) {
		if (((i - 1) * 2) >= 0) {//ӵ�и��ڵ�
			if (heap.array[(i - 1) * 2] > heap.array[i]) {//���ڵ�>�ӽڵ�
				CustomType tmp = heap.array[i];//�ݴ��½ڵ�����
				heap.array[i] = heap.array[(i - 1) * 2];//�ӽڵ����ݱ��Ϊ���ڵ�����
				heap.array[(i - 1) * 2] = tmp;//���ڵ����ݱ��Ϊ�ֽڵ�����
				i = (i - 1) * 2;//��Ϊ���ڵ�
			}
			else {//��С����������,����ѭ��,������ѭ��
				break;
			}
		}
		else {//��ӵ�и��ڵ�,����ѭ��,������ѭ��
			break;
		}
	}
}

//��������,����
/* �����һ�����ڵ�( (size-1)/2 ��λ��)�����ǰ�������и��ڵ㣨ֱ�����ڵ㣩,
ȷ��ÿһ�����ڵ㶼��һ����С�ѣ�����������γ�һ����С�� */
static void done(HEAP& heap) {
	int i = (heap.size - 1) / 2;//��β���ڵ�
	for (; i >=0; i--) {
		sorting_algorithm_down(heap, i);
	}
}

//��ʼ����
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

//�Ѳ���ڵ�
bool insert(HEAP& heap, CustomType array) {
	if (heap.size < heap.space)return false;//�ռ䳬��
	heap.array[heap.size++] = array;//���ڵ����
	sorting_algorithm_up(heap,heap.size-1);//������
	return true;
}

//����,����С�ڵ���в�����
bool come_heap(HEAP& heap, CustomType &array) {
	if (heap.size < 1)return false;
	array = heap.array[0];//���еĽڵ�����
	heap.array[0] = heap.array[heap.size-1];
	heap.array[heap.size - 1] = array;
	heap.size--;
	sorting_algorithm_down(heap, 0);
	return true;
}

//������
bool heapSort(HEAP& heap) {
	if (heap.size < 1) return false;
	while (heap.size > 0) {
		int tmp = heap.array[0];
		heap.array[0] = heap.array[heap.size - 1];
		heap.array[heap.size - 1] = tmp;
		heap.size--;
		sorting_algorithm_down(heap, 0);// ����ִ�жѵ��� 
	}
	return true;
}

//���ٶ�
void deleteHeap(HEAP& heap) {
	if (heap.array) {
		delete[] heap.array;
	}
}

int main(void) {
	HEAP hp;
	int arr[] = { 5,6,88,99,42,1,54,6,97,35,2,3,4,87,8,66,32,47,85,215,35,65,26,24,18 };
	if (!init(hp, arr, sizeof(arr) / sizeof(arr[0]))) {
		fprintf(stderr, "��ʼ����ʧ�ܣ�\n");
		exit(-1);
	}

	int i = 0; 
	CustomType array=0;
	//���Ҽ�����ǰN��С�ļ�¼
	printf("���Ҽ�����ǰN��С�ļ�¼:\n�������ռ����ݵĸ���:");
	scanf_s("%d", &i);
	while (i-- && come_heap(hp, array)) {
		printf("%d  ", array);
	}
	
	//���Ҽ�����ǰN����ļ�¼
	printf("\n���Ҽ�����ǰN����ļ�¼:\n�������ռ����ݵĸ���:");
	scanf_s("%d", &i);
	heapSort(hp);
	i = i > sizeof(arr) / sizeof(arr[0]) ? sizeof(arr) / sizeof(arr[0]) : i;
	while (i--) {
		printf(" %d", arr[i]);
	}
	system("pause");
	return 0;
}