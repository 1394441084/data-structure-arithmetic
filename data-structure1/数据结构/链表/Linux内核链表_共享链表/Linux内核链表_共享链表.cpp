#include "˫������_��������.h"
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

void The_data_carried_by_the_node_is_accessed_through_the_system();

int main(void) {
	timeDimension *cl = NULL, *s=NULL;
	STAR* sl = NULL;
	int n = 0;//Ԫ�صĸ���
	
	//��ʼ��һ���յ�˫������
	cl = new timeDimension;
	cl->fd = -1;
	Initlist(cl->node);
	sl = new STAR;
	sl->x = -1;
	Initlist(sl->node);

	//ʹ��β�巨��������
	cout << "β�巨����˫������" << endl; 
	cout << "������Ԫ�ظ��� n��"; 
	cin >> n; 
	cout << "\n ���������� n ��Ԫ�ص��ļ������" << endl;
	while (n > 0) {
		s = new timeDimension; //�����½ڵ� s 
		cin>>s->fd; 
		printf("s �ĵ�ַ:%p node: %p\n",s, &(s->node)); 
		inser_back(cl->node, s->node); 
		n--;
	}

	//��������ڵ��������
	linklist* p = NULL;
	p = &(cl->node);
	cout << "�������ӳ�ʱ�����еĽڵ�:\n";
	timeDimension* tmp = NULL;
	while (p) {
		int offset= offsetof(timeDimension, node);
		tmp = (timeDimension*)((size_t)p - offset);
		cout << tmp->fd << endl;
		p = p->next;
	}

	//��������
	p = &(cl->node);
	cout << "�������ӳ�ʱ�����еĽڵ�:\n";

	while (p) {
		int offset = offsetof(timeDimension, node);
		tmp = (timeDimension*)((size_t)p - offset);
		cout << tmp->fd << endl;
		p = p->next;
		delete tmp;
	}


	system("pause");
	return 0;
}

void The_data_carried_by_the_node_is_accessed_through_the_system() {
	timeDimension* ct = new timeDimension;
	linklist* p = &(ct->node);//�õ�node��Ա��ַ
	cout << "�����볬ʱ�ڵ��Ӧ��fd:";
	cin >> ct->fd;
	cout << "\nͨ�������ֵĽڵ���ʽڵ��ϳ��ص�����:" << endl;
	int offset = offsetof(timeDimension, node);//�õ�node��timeDimension�ĵ�ַƫ����//node��Ա���ṹ�����ʼλ��

	//�õ�node��ַƫ�Ƶ�timeDimension�ṹ����׵�ַ,�ٸ�ֵ
	timeDimension* tmp = (timeDimension*)((size_t)p - offset);
	printf("offset:%d\n", offset);//�õ�16�ֽ�,�����漰���˽ṹ���ַ����

	printf("ͨ������ڵ�node���ʵ�������:%d\n", tmp->fd);
}