#include <Windows.h> 
#include <stdio.h> 
#include <iostream> 
#include <time.h> 

constexpr auto TEST_SIZE = (1024 * 1024 * 200);
constexpr auto NUMBER = 20;

//浅试线程
int Shallow_Test_Thread();

//并行查找
int main00(void);

int main(void) {

	int* data = NULL;
	int count = 0;//记录的数量
	data = new int[TEST_SIZE];
	
	for (int i = 0; i < TEST_SIZE; i++) {
		data[i] = i;
	}

	time_t start = 0, end = 0;//记录开始和结束的时间戳
	time(&start);
	for (int j = 0; j < 10; j++) {
		for (int i = 0; i < TEST_SIZE; i++) {
			if (data[i] == NUMBER) {
				count++;
			}
		}
	}

	time(&end);
	printf("普通查找数据所花时间: %lld, count: %d\n", end - start, count);

	//多线程查找
	main00();

	//Shallow_Test_Thread();//浅试线程
	//printf("浅试线程/n");
	system("pause");
	return 0;
}