#include <Windows.h> 
#include <stdio.h> 
#include <iostream> 
#include <time.h> 

	//�߳�ִ�к�����:����ֵ������DWORD(��unsigned long); [WINAPI��д�ɲ�д(����windows��api)] ; ����������ͨ�ĺ���һ������;
static DWORD WINAPI ThreadProc(void* lpParam) { //void *lpParam ���̴߳����Ĳ��� //����������ôд,�����������Ը�
		for (int i = 0; i < 5; i++) {
			printf("�����ϰ壬�����ˣ�\n");
			Sleep(1000);
		}

		return 0;
	}


	//ǳ���߳�
	int Shallow_Test_Thread() { //���� //�ϰ�
		DWORD threadID1;//�߳� 1 �����֤		//unsigned long threadID1
		HANDLE hThread1;//�߳� 1 �ľ��			//void *hThread1

		DWORD threadID2;//�߳� 2 �����֤ 
		HANDLE hThread2;//�߳� 2 �ľ�� 

		printf("\n�����߳�... ... \n");
		//����������,��������,�ϰ�Ҳ������
		//�����߳�( �̵߳�����(һ��Ϊnull),�̶߳�ջ�Ĵ�С(0Ĭ��ֵ),�߳�ִ�еĴ���(����),���θ��߳�ִ�еĺ���,�����߳�ʱ�ı��(Ĭ��0),�̵߳�ID(�̵߳����֤��ַ));
		hThread1 = CreateThread(NULL, 0, ThreadProc, NULL, 0, &threadID1);
		//�����߳� 2 
		hThread2 = CreateThread(NULL, 0, ThreadProc, NULL, 0, &threadID2);

		//�ȴ���������(���,ʱ��(INFINITE�������));
		WaitForSingleObject(hThread1, INFINITE);//�������д˺����ȴ��̹߳������,�߳̽�����,���̲ż������д���;
		WaitForSingleObject(hThread2, INFINITE);//û�Ӵ˺����ͻ���ֽ����ϰ�ؼ���Ϣ,������ȴ��������ԭ��Ϲת;
		printf("�����ϰ延ӭ�̹߳�����\n");
		system("pause");
		return 0;
	}