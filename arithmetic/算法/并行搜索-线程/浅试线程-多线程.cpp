#include <Windows.h> 
#include <stdio.h> 
#include <iostream> 
#include <time.h> 

	//线程执行函数需:返回值必须是DWORD(即unsigned long); [WINAPI可写可不写(这是windows的api)] ; 函数名跟普通的函数一样随意;
static DWORD WINAPI ThreadProc(void* lpParam) { //void *lpParam 接线程传来的参数 //参数必须这么写,参数名倒可以改
		for (int i = 0; i < 5; i++) {
			printf("进程老板，我来了！\n");
			Sleep(1000);
		}

		return 0;
	}


	//浅试线程
	int Shallow_Test_Thread() { //进程 //老板
		DWORD threadID1;//线程 1 的身份证		//unsigned long threadID1
		HANDLE hThread1;//线程 1 的句柄			//void *hThread1

		DWORD threadID2;//线程 2 的身份证 
		HANDLE hThread2;//线程 2 的句柄 

		printf("\n创建线程... ... \n");
		//请两个工人,工人劳作,老板也在劳作
		//创建线程( 线程的属性(一般为null),线程堆栈的大小(0默认值),线程执行的代码(函数),传参给线程执行的函数,创建线程时的标记(默认0),线程的ID(线程的身份证地址));
		hThread1 = CreateThread(NULL, 0, ThreadProc, NULL, 0, &threadID1);
		//创建线程 2 
		hThread2 = CreateThread(NULL, 0, ThreadProc, NULL, 0, &threadID2);

		//等待单个对象(句柄,时间(INFINITE是无穷大));
		WaitForSingleObject(hThread1, INFINITE);//进程运行此函数等待线程工作完结,线程结束后,进程才继续运行代码;
		WaitForSingleObject(hThread2, INFINITE);//没加此函数就会出现进程老板回家休息,而工人却劳作完在原地瞎转;
		printf("进程老板欢迎线程归来！\n");
		system("pause");
		return 0;
	}