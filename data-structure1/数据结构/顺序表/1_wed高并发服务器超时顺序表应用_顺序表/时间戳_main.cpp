#include "�߲���������˳����Ӧ��_˳���.h"

void Timestamp_example();//ʱ���ʾ��

void print_the_timeout_order_table(const ssqlist<timeDimension> &tlist);//��ӡ��ʱʱ��˳���

void detectionTimeout(ssqlist<timeDimension> &tlist, time_t now);//��ʱ��⺯��
int main(void) {
	//Timestamp_example();
	time_t now, end;//����,����
	time_t timeout_detection;//��ʱ���
	time(&now);//ȡ�õ�ǰʱ��
	end = now + 60;//60����˳�ѭ��
	timeout_detection = now;
	ssqlist<timeDimension> tlist;

	//1.ģ��Ƶ������ģ��ͨ���жϷ���,���Ӷ������ӵ�˳�����
	for (unsigned int i = 0; i < 10; i++) {
		timeDimension e;
		e.fd = i;
		e.timestamp = now + 5 + 2 * i;
		tlist.Add_a_tail(e);
	}

	print_the_timeout_order_table(tlist);
	
	do {
		//Sleep(1000);//Ч�ʼ���,ʹ�ô˺���,���������������ʱ���Ǹɲ������������
		cout << "now:" << now << endl;
		if (timeout_detection + 0.999 < now) {//1���ִ�д����
			detectionTimeout(tlist,now);//��鳬ʱ������
			timeout_detection = now;//����
		}
		
		Sleep(10);//��ֹcpu���Ϲ���
		time(&now);
		
	} while (now < end);//����һ����
	

	system("pause");
	return 0;
}

void Timestamp_example() {//ʱ���ʾ��
	time_t  presentTime;//����ʱ��
	time(&presentTime);//��ȡ����ʱ��
	cout << "��ǰʱ��� - presentTime:" << presentTime << endl;
	Sleep(2000);
	time(&presentTime);//��ȡʱ��
	cout << "������ʱ��� - presentTime:" << presentTime << endl;
}

void print_the_timeout_order_table(const ssqlist<timeDimension>& tlist) {//��ӡ��ʱʱ��˳���
	cout << "˳�����ܿռ�:" << tlist.size << "\t˳����Ԫ�ظ���:" << tlist.lenth << endl;
	for (int i = tlist.head; i <= tlist.lenth - 1; i++) {
		cout << "��" << i << "��ʱ��ά�ȵľ��:" << tlist.elems[i].fd << "\t����ʱ��:" << tlist.elems[i].timestamp << endl;
		cout << "---------------------------------------------\n";
	}
	cout << endl;
}

void detectionTimeout(ssqlist<timeDimension>& tlist, time_t now) {//��ʱ��⺯��
	int fd=0, i=0;
	cout << "��鳬ʱfd...........\n";

	for (i = 0; i < tlist.lenth; i++) {
		if (tlist.elems[i].timestamp > now) {
			continue;
		}
		//��ʱ,��������
		fd = tlist.elems[i].fd;
		//�ر�����
		cout << "����[fd:" << fd << " �Ѿ���ʱ,�ر�����!\n";

		//ɾ��˳����е�Ԫ��
		if (tlist.deleteSqlist(i+1)) {
			cout << "ɾ���˵�" << i << "��Ԫ��:";
			tlist.printff();
			//ѭ����,Ԫ��ɾ����,i����++,����ƶ���ɾ��λ�õ�Ԫ���������,������:
			if (i + 1 != tlist.head) {//��Ϊ����˳���������ɾ��ͷ���Ĺ���,����
				i--;
			}
		}
	}
}