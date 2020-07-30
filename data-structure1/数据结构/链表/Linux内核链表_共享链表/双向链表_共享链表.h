#pragma once
#include <iostream>
using namespace std;

//火车一样,链表成为轮子,数据成为车厢
typedef struct _structNode {//链表实现操作
	_structNode* up = NULL;
	//int data = NULL;//节点数据
	_structNode* next = NULL;//下一个链表节点
}linklist, structNode;//链表首节点,链表节点;//这样定义能有效区分

typedef struct {//时间结构体 //进行超时管理
	int fd;	//web窗口服务句柄    //结构体地址对齐,这里多了4个字节无用的
	time_t timestamp;//超时-时间戳  //8字节
	_structNode node;//双向链表节点"挂件"//请想象成车厢
}timeDimension;//时间维度

struct STAR {
	int x; //星星的 x 坐标 
	int y; //星星的 y 坐标 
	unsigned radius; //星星的半径 
	int step; //每次跳跃的间隔 
	int color; //星星的颜色 
	_structNode node;//双向链表节点"挂件"//请想象成车厢
};

//链表初始化(linklist指针类型的引用)
bool Initlist(linklist& L) {//初始化头节点
	L.up = NULL;
	L.next = NULL;//将节点置为NULL
	return true;//初始化成功
}

//前插法 (首节点,插入的节点)
bool inser_front(linklist*& L, structNode*& node) {
	if (!L || !node)return false;//判断是否为空
	if(L->next) L->next->up = node;
	node->next = L->next;
	L->next = node;
	node->up = L;
	return true;
}

//尾插法 (首节点,插入的节点)
bool inser_back(linklist & L, structNode & node) {
	structNode* last= &L;
	while (last->next) last = last->next;//找出最后一个节点
	node.next = NULL;
	last->next = &node;
	node.up = last;
	return true;
}

/*
//双向链表输出
void single_linked_list_output(linklist*& L) {
	if (!L || L->next == L) {
		cout << "此链表为空\n";
		return;
	}
	structNode* p = L;

	while (p->next) {
		cout << p->next->data << "\t";
		p = p->next;
	}
	cout << endl;

	cout << "逆向打印:";
	while (p->up) {
		cout << p->data << "\t";
		p = p->up;
	}
	cout << endl;
}

//在指定位置插入元素
bool inser(linklist*& L, int i, int e) {
	if (!L || i <= 0)return false;//判断是否为空
	i--;//这个是插在那位置上
	structNode* last = L;
	int j = 0;
	while (last->next && j < i) {
		j++;
		last = last->next;
	}//跳出就指向那节点了
	if (!last->next && j < i)return false;//超出链条位置了

	structNode* last1 = new structNode;//新节点
	last1->data = e;

	last1->next = last->next;
	last1->up = last;
	if (last->next) last->next->up = last1;
	last->next = last1;
	
	return true;
}

//按位置删除元素
bool linked_list_delete_site(linklist*& L, int i) {
	if (!L || !L->next || i <= 0) { return false; }//判断是否为空
	structNode* last = L;

	int j = 1;

	while (last->next && i > j) {
		last = last->next;
		j++;
	}//跳出就指向那节点了

	if (!last->next || j < i)return false;

	structNode* last1;
	last1 = last->next;//1
	last->next = last1->next;//1=3
	if(last1->next) last1->next->up = last;
	delete last1;
	return true;//数据对上了,返回
}

//销毁链表
void linked_list_delete(linklist*& L) {
	if (!L) return;
	structNode* last = L;
	while (last) {
		L = L->next;//指向下一个节点
		//cout << "删除元素:" << last->data << endl;
		delete last;//删除头节点
		last = L;
	}
}

void single_linked_list_main() {
	linklist* L = NULL;//创建首节点
	if (Initlist(L)) { cout << "初始化成功\n"; }
	else { exit(-1); }//初始化一个空的链表
	int n = 0; structNode* s = NULL; int x = 0;

	cout << "前插法创建单链表\n";
	cout << "请输入元素个数:";
	cin >> n;
	cout << "\n请依次输入" << n << "个元素:\n";

	while (n > 0) {
		s = new structNode;//生成新节点
		cin >> s->data;
		inser_front(L, s);
		--n;
	}

		single_linked_list_output(L);

		cout << "后插法创建单链表\n";
		cout << "请输入元素个数:";
		cin >> n;
		cout << "\n请依次输入" << n << "个元素:\n";

		while (n > 0) {
			s = new structNode;//生成新节点
			cin >> s->data;
			inser_back(L, s);
			--n;
		}

		single_linked_list_output(L);

		//在任意位置插入
		cout << "指定位置插入元素\n";
		cout << "请输入插入位置和元素(用空格隔开):\n";
		while (cin >> n >> x) {
			if (inser(L, n, x)) single_linked_list_output(L);
			else cout << "插入失败\n";
		}

		single_linked_list_output(L);


}*/