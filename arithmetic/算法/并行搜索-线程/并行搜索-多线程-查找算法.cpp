#include <Windows.h> 
#include <stdio.h> 
#include <iostream> 
#include <time.h> 

constexpr auto TEST_SIZE = (1024 * 1024 * 200); 
constexpr auto NUMBER = 20;

typedef struct _search{ 
	int *data;//���������ݼ� 
	size_t start; //�����Ŀ�ʼλ�� 
	size_t end; //��������ֹλ�� 
	size_t count; //�������
}search; 

namespace {
	//�߳���������
	DWORD WINAPI ThreadProc(void* lpParam) {
		static int i = 0;
		search* s = (search*)lpParam;
		time_t start, end;
		printf("�µ��߳̿�ʼִ��...\n");
		time(&start);
		for (int j = 0; j < 10; j++) {//��ʼ���� NUMBER
			for (size_t i = s->start; i <= s->end; i++) {
				if (s->data[i] == NUMBER) {
					s->count++;
				}
			}
		}
		time(&end);
		printf("�߳� %d ������������ʱ��: %lld\n", ++i, end - start);
		return 0;
	}
}

//���в���
int main00(void){ 
	int *data = NULL; 
	int count = 0;//��¼������
	int mid = 0;
	search s1, s2;

	//��ʼ������ҵĴ�������
	data = new int[TEST_SIZE]; 
	for (int i = 0; i < TEST_SIZE; i++) {
		data[i] = i;
	}

	mid = TEST_SIZE / 2;//�м�ֵ

	//��һ���߳�����ҵķ�Χ
	s1.data = data;
	s1.start = 0; 
	s1.end = mid; 
	s1.count = 0;

	//�ڶ����߳�����ҵķ�Χ
	s2.data = data; 
	s2.start = mid + 1;
	s2.end = TEST_SIZE - 1; 
	s2.count = 0; 

	//�����߳�:
	DWORD threadID1;//�߳� 1 �����֤
	HANDLE hThread1;//�߳� 1 �ľ�� 
	DWORD threadID2;//�߳� 2 �����֤ 
	HANDLE hThread2;//�߳� 2 �ľ�� 

	printf("\n�����߳�... ... \n"); 
	//�����߳� 1
	hThread1 = CreateThread(NULL, 0, ThreadProc, &s1, 0, &threadID1);
	//�����߳� 2 
	hThread2 = CreateThread(NULL, 0, ThreadProc, &s2, 0, &threadID2);

	WaitForSingleObject(hThread1, INFINITE);
	WaitForSingleObject(hThread2, INFINITE); 
	printf("�����ϰ延ӭ�̹߳�����count: %d\n", s1.count+s2.count); 
	system("pause");
	return 0; 
}

