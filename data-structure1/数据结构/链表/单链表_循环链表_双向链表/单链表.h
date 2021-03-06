#pragma once
#include <iostream>
using namespace std;

//链表概念:请百度链表就能知道是啥了,真是个抖机灵
typedef struct _structNode {//链表实现操作
	 int data=NULL;//节点数据
	_structNode* next=NULL;//下一个链表节点
}linklist, structNode;//链表首节点,链表节点;//这样定义能有效区分

//单链表的初始化(linklist指针类型的引用)
bool Initlist(linklist*  &L) {//只初始化头节点
	L = new structNode;//生成一个节点

	if (!L)return false;//生成节点失败
	L->data=NULL;
	L->next = NULL;//将节点置为NULL
	return true;//初始化成功
}

//前插法 (首节点,插入的节点)
bool inser_front(linklist* &L, structNode* &node) {
	if (!L || !node)return false;//判断是否为空
	/*
	
	if (L->next == NULL) {
		L->data = node->data;
		node->data = NULL;
		node->next = NULL;
		L->next = node;
	}
	else {
		L->data = node->data;
		node->data = L->data;
		node->next = L->next;//原首节点的下一个节点地址,由进来的,新的下一个节点接管
		L->next = node;//首节点的下一个节点地址替换成新节点地址
	}*/

	//L->data = node->data;//0=1:1 1=2:L=2 2=3:L=3
	//node->data = L->data;//1=0:0 2=1:n=1 3=2:n=2
	node->next = L->next;//原首节点的下一个节点地址,由进来的,新的下一个节点接管
	L->next = node;//首节点的下一个节点地址替换成新节点地址

		return true;
}

//后插法()
bool inser_back(linklist* &L, structNode* &node) {
	if (!L || !node)return false;//判断是否为空
	structNode *last=L;//尾部
	while (last->next) { 
		last =last->next;
	}//跳出就指向尾部节点了
	
	node->next = NULL;//新尾节点->next置为NULL
	last->next = node;//尾节点->next指向新节点,新节点变为新尾节点
	return true;
}

//在指定位置后插入
bool inser(linklist*& L,int i,int &e) {
	if (!L || i <= 0 )return false;//判断是否为空
	i--;//这个是插在那位置上
	structNode* last = L;
	int j = 0;
	while (last->next && j<i) {
		j++;
		last = last->next;
	}//跳出就指向那节点了
	if (!last->next && j < i)return false;//超出链条位置了

	structNode* last1 = new structNode;//新节点
	last1->data = e;
	last1->next = last->next;
	last->next = last1;

	return true;
}

//单链表取值
bool linked_list_value(linklist*& L, int i, int& e) {
	if (!L || !L->next || i<=0)return false;//判断是否为空
	structNode* last = L->next;
	int j = 1;

	while (last->next && j < i) {
		j++;
		last = last->next;
	}//跳出就指向那节点了

	if (!last->next && j < i)return false;//超出链条位置了

	e = last->data;

	return true;
}

//单链表查找元素
bool linked_list_search_data(linklist*& L, int data,int & i) {//按值查找
	if (!L || !L->next) {i = -1;return false;}//判断是否为空
	structNode* last = L->next;
	i = 1;
	while (last) {
		if (last->data == data)return true;//数据对上了,返回
		i++;
		last = last->next;
	}//跳出就指向那节点了

	i = -1;
	return false;
}

//单链表删除元素数据
bool linked_list_delete_data(linklist*& L, int data) {
	if (!L || !L->next) {return false; }//判断是否为空
	structNode* last = L;
	
	while (last->next) {
		if (last->next->data == data) {//1
			structNode* last1;
			last1 = last->next;//1
			last->next = last1->next;//1=3
			delete last1;
			return true;//数据对上了,返回
		}
		last = last->next;
	}//跳出就指向那节点了

	return false;
}

//单链表按位置删除元素
bool linked_list_delete_site(linklist*& L, int i) {
	if (!L || !L->next ||i<=0) { return false; }//判断是否为空
	structNode* last = L;
	
	int j = 1;

	while (last->next && i>j) {
		last = last->next;
		j++;
	}//跳出就指向那节点了

	if (!last->next || j < i)return false;

	structNode* last1;
	last1 = last->next;//1
	last->next = last1->next;//1=3
	delete last1;
	return true;//数据对上了,返回
}

//销毁单链表
void linked_list_delete(linklist*& L) {
	structNode* last = L;
	while (last) {
		L = L->next;//指向下一个节点
		//cout << "删除元素:" << last->data << endl;
		delete last;//删除头节点
		last = L;
	}
}

//单链表输出
void single_linked_list_output(linklist* &L) {
	if (!L) {
		cout << "此链表为空\n";
		return;
	}
	structNode* p = L->next;
	
	while (p) {
		cout << p->data << "\t";
		p = p->next;
	}
	cout << endl;
}


void single_linked_list_main() {
	linklist* L = NULL;//创建首节点
	Initlist(L);//初始化一个空的链表
	
	//使用前插法插入数据
	int n=0; structNode* s = NULL; int x = 0;

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

	//单链表的输出
	single_linked_list_output(L);
	
	//使用后插法插入数据
	//int n; structNode* s = NULL;
	cout << "后插法创建单链表\n";
	cout << "请输入元素个数:";
	cin >> n;
	cout << "\n请依次输入" << n << "个元素:\n";

	while (n > 0) {
		s = new structNode;//生成新节点
		cin >> s->data;
		inser_back(L, s);//正常的进行中
		n--;
	}
	
	//单链表的输出
	single_linked_list_output(L);

	//在任意位置插入元素
	for(int i=0;i<-3;i++){
		cout << "请输入插入位置和元素(用空格隔开):\n";
		cin >> n >> x;
		
		if (inser(L,n,x)) {single_linked_list_output(L);}
		else {cout << "插入失败!\n";}
	}
	
	//按指定位置取单链表值
	for (int i = 0; i < -6; i++) {
		cout << "请输入取值位置:\n";
		cin >> n;
		if (linked_list_value(L, n, x)) {
			cout << "链表的第" << n << "个元素:" << x << endl;
		}
		else {
			cout << "取指失败!\n";
		}
	}

	//按元素(存储的数据)来查询在单链表是否存储,返回在哪个位置
	//cout << "请输入需查找的元素:\n";
	//while(cin>>n){
		while (0) {
		if (linked_list_search_data(L, n, x)) {
			cout << "元素: " << n << " 在链表的第" << x <<"位置."<< endl;
		}
		else {
			cout << "没有此元素\n";
		}
		cout << "请输入需查找的元素:\n";
	}
	
	//按指定位置删除元素 
		//cout << "请输入需删除的位置:" ;
		//while (cin >> n) {
			while (0) {
			if (linked_list_delete_site(L, n)) {
				cout << "已成功删除第" << n << "位置的空间\n";
				single_linked_list_output(L);
			}
			else {
				cout << "没有此位置的空间,请再次输入\n";
				single_linked_list_output(L);
			}
			cout << "请输入需删除的位置:";
		}

		//按元素数据删除
		//cout << "请输入需删除的元素:";
		//while (cin >> n) {
			while (0) {
			if (linked_list_delete_data(L, n)) {
				cout << "已成功删除为 " << n << " 的元素空间\n";
				single_linked_list_output(L);
			}
			else {
				cout << "没有此元素,请再次输入\n";
				single_linked_list_output(L);
			}
			cout << "请输入需删除的位置:";
		}

		//销毁单链表
		linked_list_delete(L);
}