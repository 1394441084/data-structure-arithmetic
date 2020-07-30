#include "双向链表_共享链表.h"
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

void The_data_carried_by_the_node_is_accessed_through_the_system();

int main(void) {
	timeDimension *cl = NULL, *s=NULL;
	STAR* sl = NULL;
	int n = 0;//元素的个数
	
	//初始化一个空的双向链表
	cl = new timeDimension;
	cl->fd = -1;
	Initlist(cl->node);
	sl = new STAR;
	sl->x = -1;
	Initlist(sl->node);

	//使用尾插法插入数据
	cout << "尾插法创建双向链表" << endl; 
	cout << "请输入元素个数 n："; 
	cin >> n; 
	cout << "\n 请依次输入 n 个元素的文件句柄：" << endl;
	while (n > 0) {
		s = new timeDimension; //生成新节点 s 
		cin>>s->fd; 
		printf("s 的地址:%p node: %p\n",s, &(s->node)); 
		inser_back(cl->node, s->node); 
		n--;
	}

	//根据链表节点访问数据
	linklist* p = NULL;
	p = &(cl->node);
	cout << "遍历连接超时链表中的节点:\n";
	timeDimension* tmp = NULL;
	while (p) {
		int offset= offsetof(timeDimension, node);
		tmp = (timeDimension*)((size_t)p - offset);
		cout << tmp->fd << endl;
		p = p->next;
	}

	//销毁链表
	p = &(cl->node);
	cout << "销毁连接超时链表中的节点:\n";

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
	linklist* p = &(ct->node);//得到node成员地址
	cout << "请输入超时节点对应的fd:";
	cin >> ct->fd;
	cout << "\n通过链表种的节点访问节点上承载的数据:" << endl;
	int offset = offsetof(timeDimension, node);//得到node到timeDimension的地址偏移量//node成员到结构体的起始位置

	//得到node地址偏移到timeDimension结构体的首地址,再赋值
	timeDimension* tmp = (timeDimension*)((size_t)p - offset);
	printf("offset:%d\n", offset);//得到16字节,这里涉及到了结构体地址对齐

	printf("通过链表节点node访问到的数据:%d\n", tmp->fd);
}