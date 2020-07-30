#include <Windows.h> 
#include <stdio.h> 
#include <iostream> 
#include <time.h> 

constexpr auto TEST_SIZE = (1024 * 1024 * 200); 
constexpr auto NUMBER = 20;

typedef struct _search{ 
	int *data;//搜索的数据集 
	size_t start; //搜索的开始位置 
	size_t end; //搜索的终止位置 
	size_t count; //搜索结果
}search; 

namespace {
	//线程搜索函数
	DWORD WINAPI ThreadProc(void* lpParam) {
		static int i = 0;
		search* s = (search*)lpParam;
		time_t start, end;
		printf("新的线程开始执行...\n");
		time(&start);
		for (int j = 0; j < 10; j++) {//开始查找 NUMBER
			for (size_t i = s->start; i <= s->end; i++) {
				if (s->data[i] == NUMBER) {
					s->count++;
				}
			}
		}
		time(&end);
		printf("线程 %d 查找数据所花时间: %lld\n", ++i, end - start);
		return 0;
	}
}

//并行查找
int main00(void){ 
	int *data = NULL; 
	int count = 0;//记录的数量
	int mid = 0;
	search s1, s2;

	//初始化需查找的大量数据
	data = new int[TEST_SIZE]; 
	for (int i = 0; i < TEST_SIZE; i++) {
		data[i] = i;
	}

	mid = TEST_SIZE / 2;//中间值

	//第一个线程需查找的范围
	s1.data = data;
	s1.start = 0; 
	s1.end = mid; 
	s1.count = 0;

	//第二个线程需查找的范围
	s2.data = data; 
	s2.start = mid + 1;
	s2.end = TEST_SIZE - 1; 
	s2.count = 0; 

	//创建线程:
	DWORD threadID1;//线程 1 的身份证
	HANDLE hThread1;//线程 1 的句柄 
	DWORD threadID2;//线程 2 的身份证 
	HANDLE hThread2;//线程 2 的句柄 

	printf("\n创建线程... ... \n"); 
	//创建线程 1
	hThread1 = CreateThread(NULL, 0, ThreadProc, &s1, 0, &threadID1);
	//创建线程 2 
	hThread2 = CreateThread(NULL, 0, ThreadProc, &s2, 0, &threadID2);

	WaitForSingleObject(hThread1, INFINITE);
	WaitForSingleObject(hThread2, INFINITE); 
	printf("进程老板欢迎线程归来！count: %d\n", s1.count+s2.count); 
	system("pause");
	return 0; 
}

