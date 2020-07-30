#include <Windows.h> 
#include <stdio.h> 
#include <iostream> 
#include <time.h> 

constexpr auto TEST_SIZE = (1024 * 1024 * 200);
constexpr auto NUMBER = 20;

//ǳ���߳�
int Shallow_Test_Thread();

//���в���
int main00(void);

int main(void) {

	int* data = NULL;
	int count = 0;//��¼������
	data = new int[TEST_SIZE];
	
	for (int i = 0; i < TEST_SIZE; i++) {
		data[i] = i;
	}

	time_t start = 0, end = 0;//��¼��ʼ�ͽ�����ʱ���
	time(&start);
	for (int j = 0; j < 10; j++) {
		for (int i = 0; i < TEST_SIZE; i++) {
			if (data[i] == NUMBER) {
				count++;
			}
		}
	}

	time(&end);
	printf("��ͨ������������ʱ��: %lld, count: %d\n", end - start, count);

	//���̲߳���
	main00();

	//Shallow_Test_Thread();//ǳ���߳�
	//printf("ǳ���߳�/n");
	system("pause");
	return 0;
}